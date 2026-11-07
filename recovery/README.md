# APM32F030 固件完整重建

已从 `stm32_fw.hex` 重建完整汇编工程、全固件 C 语义模型、433 个函数的 C 反编译稿，并整理了关键业务的可读 C。**完整汇编工程可以独立构建出与原固件逐字节一致的 64 KiB 映像。** 这不是找回了原作者的工程目录、变量名和注释；这些信息没有保留在 HEX 中。

**原始 `../stm32_fw.hex` 绝对不能修改、删除或覆盖，包括格式与换行调整。** 它是恢复工作的不可变验证基准；修改和实验必须使用独立副本，构建产物只能写入输出目录。原文件摘要及具体要求见[仓库 README 的原始 HEX 文件保护规则](../README.md#原始-hex-文件保护规则必须遵守)。

## 使用入口

| 需要做什么 | 入口 | 可构建性 |
|---|---|---|
| 重新生成整个原固件 | [full_assembly/](full_assembly/README.md) | GNU ARM 汇编、链接，输出 ELF/BIN/HEX；无 `.incbin`，不依赖原 BIN 进行构建 |
| 查看全部指令对应的 C 语义 | [full_c/](full_c/README.md) | 可编译的电脑端 C 模型，所有已识别代码均译成显式 C 操作；不是 MCU 原生 C 固件 |
| 按函数阅读类似原代码的表达式/控制流 | [433 个函数索引](decompiled/README.md) | Ghidra C 反编译参考，含自动推断类型和警告，不是可直接链接的工程 |
| 阅读整理过的启动、升级、协议和业务 | [代码地图](MODULE_MAP.md)、[reconstructed/](reconstructed/) | 重点函数与主循环译文；外部依赖保留原地址名 |

在仓库根目录运行：

```sh
make -C recovery
make -C recovery verify
```

只构建板上固件：

```sh
make -C recovery/full_assembly verify
```

板上固件输出为 `recovery/full_assembly/build/firmware.elf`、`firmware.bin`、`firmware.hex`。构建依赖本机已安装的 `arm-none-eabi-as/ld/objcopy`。完整 C 模型使用本机 C 编译器，差分验证另使用已安装的 Python Unicorn/Capstone。测试不访问主板，也没有执行烧录。

## 完整性与验证

- 全部 **65536 字节**逐字节一致；BIN SHA-256 为 `3016dafb97375b22cdb49f1ed41b05c7f1aa940d58c5ce42c2fdbe682245a144`。
- 已把三个汇编源码构建文件复制到空临时目录，在**不带原 HEX/BIN**的条件下重建并通过对比。源码包含 Boot、App、向量、常量、元数据和配置，没有把缺失驱动替换成空函数。
- **21069 条已识别 Thumb 指令、44750 字节指令区**。其中20732条为助记符；337条因汇编器选择不同等价编码而用 `.inst` 保留原编码，旁边仍附助记符和原因。
- 8个 Keil switch8 表、656个 literal pool；原未分类的509字节已逐段审计，补入20字节明确指令、确认120字节常量，剩余369字节按填充候选保留。见 [间隙与间接调用审计](full_assembly/gap_audit.md)。
- Ghidra 导出433个函数，无导出失败。最终433个函数体覆盖21059条指令，额外10条未引用/冗余指令由完整汇编和完整C模型明确保留，不伪称反编译器已经识别全部原函数。
- 主循环：1053条已识别指令均有显式 C 控制流，347场景对比通过，动态覆盖695条，并比较23873个外部调用事件。它是 CPU 上下文模型，不是原作者风格的 `main.c`。
- 命令分派：10752例通过，659/660条动态覆盖（剩余为无已知入口的冗余跳转）。标识符状态处理：2777例通过，751/751条动态覆盖。
- 先前的串口10400个字节步骤、256种发送长度、200组参数、通道/命令5360例和CRC5组对照均保留。
- 完整C模型：42138组单指令对照、1354组完整函数执行对照，以及非对齐访问/首次故障保持等边界验证通过；另有独立的3584组移位与进借位边界对照通过。见 [full_c/](full_c/README.md)。各报告区分原指令执行、脚本化外部调用与硬件未建模范围。

**原 HEX 与新构建 HEX 解码后的 Flash 地址和数据完全一致，不同字节数为0；两个 HEX 文本文件本身不完全相同。** 分行、记录长度等格式差异不改变所表示的 Flash 数据。上面的 SHA-256 是原 HEX 解码映像与重建 BIN 的摘要，不是 HEX 文本的摘要。比对范围为 `0x08000000–0x0800FFFF`，独立构建与复现入口见[仓库 README](../README.md)。

字节一致验证的是汇编构建；有限输入的差分验证验证相应 C 路径。两者都不能被扩大解释为“原始源码名字和类型已找回”或“所有电气时序、IRQ并发、外接设备都已模拟”。

## 主板与存储布局

用户提供的 [`主板.png`](../主板.png) 中主控 U11 为 **Geehy APM32F030C8T6**，晶振标记8.000，接口有“刷卡模块”，U8/U9与NXP 74HC595D相符。Geehy [官方选型资料](https://geehy.com/uploads/tool/Geehy%20MCU%20Selection%20Guide-2022.4.11.pdf)列该型号为Cortex-M0+、64 KiB Flash、8 KiB RAM。固件匹配F030兼容向量/寄存器布局；没有连接设备读取芯片ID。

| 地址（含首尾） | 用途 |
|---|---|
| `08000000–08003FFF` | Boot分区，main=`08002CF4` |
| `08004000–0800F7FF` | App分区，main=`0800A708`；`0800CF28`起长FF区 |
| `0800F800–0800FBFF` | 升级元数据；文件名`app.bin`，当前`F802=FFFF` |
| `0800FC00–0800FFFF` | 配置页，全部原始字节保留 |

HEX全部2050条记录校验通过、连续64 KiB、无空洞；原HEX SHA-256：`22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf`。原文件未修改。

## 重点代码

- [startup_boot.c](reconstructed/startup_boot.c)：启动、RAM初始化、Boot等待、应用交接。
- [firmware_update.c](reconstructed/firmware_update.c)：CRC、单包接收、Flash更新、I2C暂存后提交。
- [serial_protocol.c](reconstructed/serial_protocol.c)：组帧、XOR校验、发包、23字节参数映射。
- [application.c](reconstructed/application.c)：12路状态、计时、74HC595输出、显示、PB10命令、I2C存储。
- [application_main.c](reconstructed/application_main.c)：完整主循环C控制流和93槽定时器分派。
- [business_handlers.c](reconstructed/business_handlers.c)：`B0DC`全部命令分派与`9694`标识符状态处理。

这些阅读层级存在有意的重复实现，不要把所有 `.c` 简单拼接成 MCU 工程。完整固件构建走 `full_assembly`；完整C执行模型走 `full_c`；人工作品用于核对、理解和继续模块化重构。

## REA/Ghidra 与复现

最初 Hopper 试用版无法保存工程，大函数处理也未顺利完成。本轮使用官方 Ghidra 12.1.4，下载包对照GitHub官方SHA-256通过后，从随包源码构建了macOS ARM64反编译器，再经REA 6.8.0 CLI成功导出。工具来源、摘要与构建参数见 [tool_source.json](ghidra/tool_source.json)。仅使用每条命令的环境变量，没有更改全局REA/MCP配置。

最终证据见 [rea-final-decompile-result.json](ghidra/rea-final-decompile-result.json)，Evidence ID `ev_1da03b3d2a8311a39a50a119a983782002a3b6f8b6b69061838f3bb5d7658dfe`。输入是完整汇编构建的ELF，SHA-256 `3ad2cf305acb090aef48d1b21055d4a0d2862daa8262946f3eed124b47537bcf`；其Flash字节与原HEX一致。各函数名称仍是分析名称，原始ELF没有找回。

```sh
python3 recovery/ghidra/export_all.py --output recovery/decompiled-fresh
python3 recovery/tools/audit_recovery.py
```

Ghidra输出保留所有警告；函数索引中的文件SHA-256、输入ELF身份及覆盖范围由审计脚本检查。移动源码目录后，REA的路径绑定可能变化，重新导出应选择新的输出目录。早期分析文件保留在工作区 `ghidra/initial_decompile` 和 `ghidra/prior_classification_decompile`（源码压缩包省略这两份过期副本），当前阅读以 `decompiled` 为准。

## 保留的边界

已知待修复项：人工译文 [application.c](reconstructed/application.c) 的 I²C 就绪轮询把原始五参数调用写成了四参数调用，尚未修复。它不参与 `full_assembly` 的构建，因此不影响汇编产物与原固件的字节一致性；现有 C 差分验证也未覆盖这段手工译文。

完整代码/数据已经有可重建表示；完整C模型覆盖所有已识别指令。仍未找回原工程模块划分、原变量名/注释、确切编译器选项，部分测量/计费字段物理单位和外部模块型号也没有证据。动态DMA/UART回调目标不能仅凭静态指针表证明穷尽；完整C模型遇到未分类PC、缺少外设总线实现或不支持的异常返回会明确报错，不返回虚假的成功。

若要变成适合日常开发的纯C、APM32 SDK工程，还需要在这些完整表示上进行模块化重构、驱动整合和板级对照；**当前可以独立构建的原生固件是完整汇编工程，不是宣称原始纯C工程已经找回。**
