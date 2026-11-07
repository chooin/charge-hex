# 完整、可重建的地址固定汇编工程

此目录提供整个 `stm32_fw.hex` 的 GNU ARM 汇编表示，包括 Bootloader、App、向量、常量、升级元数据、配置与显式填充值。**不是原始 C 源码工程，也不是把 BIN 通过 `.incbin` 打包**：控制流识别出的指令以 Thumb 助记符表示；已知数据和仍不能确定为代码的字节明确写成 `.word` / `.byte`。

构建结果的全部 65536 字节与原始 HEX 解码内容逐字节一致：

`3016dafb97375b22cdb49f1ed41b05c7f1aa940d58c5ce42c2fdbe682245a144`

## 构建

```sh
make -C recovery/full_assembly verify
```

产物：`build/firmware.elf`、`build/firmware.bin`、`build/firmware.hex`。构建仅需 GNU `arm-none-eabi-as/ld/objcopy`；源码不依赖原 HEX/BIN。验证另用 Python 的严格 HEX 解码器直接读取仓库根目录原始 `stm32_fw.hex`。

`firmware.S` 是实际构建源码；`firmware.ld` 固定映像起点 `0x08000000` 和64KiB大小。HEX 文本的行宽、入口地址记录可能与原文件不同，但 Flash 地址与每个字节一致。没有连接设备或执行烧录。

## 指令发现与可维护边界

`generate.py` 使用 Capstone ARMv6-M Thumb 递归控制流遍历，入口来自两组向量、已核对的启动/main/运行时函数、直接调用及受限的 Flash 指针启发式。遇到返回和无返回入口会停止顺序遍历；识别 PC 相对 literal pool；专门解码8处 Keil `__switch8` 内联跳转表，防止把跳转表当指令。

- `.L_0800xxxx`：固定地址标签。
- `fw_0800xxxx`：分析者分配的候选函数入口别名，并非原始符号。
- `boot_main` / `app_main` / 两个 Reset 别名：已核对的入口。
- `.word` / `.byte` 注释区分向量、literal、switch表和未分类字节。
- 少数 ADD/SUB 与 NOP 指令由于 GNU assembler 自动选择另一种等价编码，使用 `.inst.n` 保留精确编码，旁边仍附完整助记符及原因。这些并非未解码指令；详细地址列在 `coverage.json`。

原程序含绝对 Flash 地址、函数地址和内联跳转表，因此此版本优先**固定原地址和指令宽度**。在这个目录修改指令长度或挪动代码时，不能假设数字常量和表自动随之更新；需同时更新指针/表/布局并重新验证。它可以作为完整反汇编源码、分析和逐函数替换的基础，不能宣称已经得到原作者的模块化 C 工程。

## 文件与可复核性

| 文件 | 用途 |
|---|---|
| `firmware.S` | 完整助记符和显式数据源 |
| `firmware.ld` / `Makefile` | 无原始BIN输入的构建 |
| `coverage.json` | 指令/数据字节、内联表、未分类区间、编码回退及间接分支限制 |
| `instructions.json` | 指令地址、长度、原字节、Capstone助记符 |
| `seeds.json` | 每个入口及其发现原因 |
| `roundtrip_result.json` | 对原始HEX的独立逐字节校验结果 |
| `gap_audit.md` / `gap_audit.json` | 原199段509字节的逐段审计，以及12处间接调用/跳转解释 |
| `generate.py` | 从已验证BIN重新生成，依赖已安装的Python Capstone |

生成器运行方式：`python3 recovery/full_assembly/generate.py`。不要在手工修改 `firmware.S` 后运行生成器覆盖自己的工作。

**验证边界**：字节完全相同保证了原映像字节被保留，并不单独证明每个代码/数据分类都正确、所有间接调用目标都已命名，或业务语义已经恢复。未分类区间始终保留并列出。具体函数人工整理与局部机器码差分验证另见 `../reconstructed/` 和 `../README.md`。
