# Charge 固件开发与恢复基准

日常开发入口现在位于 [`firmware/`](firmware/README.md)：协议、参数规则、通道、计时和存储服务使用可独立编译的 C 模块；硬件地址及旧固件调用约定集中在平台适配层。整体设计、迁移范围及依据见[架构说明](docs/architecture.md)，当前验收见[验证记录](docs/verification.md)。

```sh
make             # 主机 C 库 + ARM 渐进重构固件
make test        # 主机行为、架构边界及原始 Thumb 差分
make verify      # 另验证新固件布局、实际 ARM C 入口及调用链
make verify-recovery  # 独立复验原恢复工程
```

`make verify` 和 `make verify-recovery` 会重新构建并创建独立的
`recovery/build/verification/<run-id>/`。该目录的 `run.json` 记录源码/原始输入摘要、
工具版本、实际构建参数、步骤结果和产物摘要，并保留日志与固件副本。
本次结果不会覆盖已提交的历史验证报告；具体路径会打印到终端。

新输出为 `firmware/build/charge.{elf,bin,hex}`，其中七个旧入口已经接入 C 模块，其余程序通过原汇编兼容层运行。**这是渐进重构的开发版本，尚未完成全部高层 C 迁移或板级验收；它与原固件不再字节一致。** 下文的字节一致性结论只针对 `recovery/full_assembly`。协议解析、计时和升级 CRC 的新 C API 已可独立使用，但原整机对应路径仍保留旧实现。

## 固件源码重建基准

从 `stm32_fw.hex` 与 `主板.png` 恢复的代码和构建工程位于 [`recovery/`](recovery/README.md)。主板主控为 Geehy APM32F030C8T6。

## 原始 HEX 文件保护规则（必须遵守）

**仓库根目录的 `stm32_fw.hex` 是原始固件证据和全部恢复工作的验证基准，绝对不能修改、删除或覆盖。** 本规则适用于人工操作、脚本、构建工具及 AI 代理。

- 原文件只能读取。任何字节都必须保留，包括换行、字符大小写和记录顺序；即使格式调整后的 Flash 内容相同，也禁止改写原文件。
- 需要修改、转换格式或进行实验时，先复制到独立路径，再操作副本。编译产物保存到 `recovery/full_assembly/build/` 等输出目录，**不得用新生成的 HEX 替换原始 `stm32_fw.hex`**。
- 原文件是独立的比对依据。若用重建产物覆盖它，后续验证就可能变成产物与自身比较，失去证明恢复结果是否正确的意义。
- 如果发现原文件摘要不符，应停止使用它进行一致性验证，从已核验的原始备份恢复；禁止修改校验记录来掩盖差异。

原始 **HEX 文件本身**的 SHA-256（包含原始文本格式与换行）固定为：

```text
22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf
```

可在仓库根目录执行以下只读命令核对，结果应与上述摘要一致：

```sh
shasum -a 256 stm32_fw.hex
```

## 编译产物与原固件的比对结果

**当前 `full_assembly` 汇编源码重新编译后，生成的 Flash 映像与原始 `stm32_fw.hex` 解码后的内容逐字节完全一致。**

| 比对项 | 结果 |
|---|---|
| Flash 地址范围 | `0x08000000–0x0800FFFF` |
| 映像大小 | 65,536 字节（64 KiB） |
| 不同字节数 | **0** |
| 原 HEX 与新 HEX 解码后的地址、数据 | **完全一致** |
| 原 HEX 与新 HEX 的文本内容 | 不完全相同，分行和记录格式有差异 |

原 HEX 解码得到的 BIN 与新构建的 `firmware.bin`，SHA-256 均为：

```text
3016dafb97375b22cdb49f1ed41b05c7f1aa940d58c5ce42c2fdbe682245a144
```

这个摘要针对 **Flash 二进制映像**，不是 HEX 文本文件。Intel HEX 是带地址和校验信息的文本格式；同一份 Flash 数据可以采用不同的记录长度和分行方式，因此不能只用两个 HEX 文件的文本 diff 或文件哈希判断固件是否一致。

验证时已将 `firmware.S`、`firmware.ld`、`Makefile` 复制到空临时目录，在不携带原 HEX/BIN 的条件下独立构建，再与原固件比较。详情见[独立重建验证报告](recovery/full_assembly/roundtrip_result.json)。该结论对应已核验的源码版本，修改代码后应重新验证。

## 构建与验证

在仓库根目录执行，只构建原生固件并核对内容：

```sh
make -C recovery/full_assembly verify
```

| 输出文件 | 用途 |
|---|---|
| `recovery/full_assembly/build/firmware.bin` | 完整 64 KiB Flash 二进制映像 |
| `recovery/full_assembly/build/firmware.hex` | 带地址信息的 Intel HEX 固件 |
| `recovery/full_assembly/build/firmware.elf` | 汇编工程的链接产物，含分析符号 |

构建全部产物（同时包括电脑端 C 语义模型），并运行整套验证：

```sh
make -C recovery
make -C recovery verify
```

## 代码入口与适用范围

- [完整汇编工程](recovery/full_assembly/README.md)：从源码独立构建 ELF/BIN/HEX，全部64 KiB与原固件逐字节一致。
- [完整 C 语义模型](recovery/full_c/README.md)：全部已识别指令的可编译C表达，用于电脑端分析和验证。
- [全函数 C 反编译稿](recovery/decompiled/README.md)：433个函数，保留反编译警告。
- [代码阅读地图](recovery/MODULE_MAP.md)：人工整理的启动、升级、协议、主循环、业务逻辑入口。

**上述字节一致性结论适用于 `full_assembly` 的固件构建。** C 语义模型与反编译稿不等同于已经找回的原始纯 C/Keil 工程，不能将该结论推广为所有 C 译文均已验证正确。

已知待修复项：人工译文 [application.c](recovery/reconstructed/application.c) 的 I²C 就绪轮询将原始五参数调用误写为四参数调用，目前尚未修复。该 C 文件不参与汇编固件构建，因此上述固件映像仍与原始字节一致。

原 HEX 未修改。验证未连接主板、未执行烧录，尚未进行板级运行验证。
