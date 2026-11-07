# HEX 清单与映像结构

本记录来自 `stm32_fw.hex` 的静态字节、ARM Thumb 反汇编、ST 官方启动模板比对，以及主分析者对用户新增 `主板.png` 的检查。未执行固件。`parse_hex.py` 是分析期间新写的工具，不是原始固件源码。

## 文件完整性

- 原始文件：157,726 字节，SHA-256 `22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf`。
- 2,050 条 Intel HEX 记录：1 条扩展线性地址、2,048 条数据、1 条 EOF。每条记录的长度、语法和 checksum 均通过；无重叠、无空洞、无 EOF 后记录。
- 数据连续覆盖 `[0x08000000, 0x08010000)`，共 65,536 字节。末尾 FF 也是文件显式保存的字节。
- 二进制 SHA-256 `3016dafb97375b22cdb49f1ed41b05c7f1aa940d58c5ce42c2fdbe682245a144`。
- 独立使用 `arm-none-eabi-objcopy -I ihex -O binary` 转换后，与 `parse_hex.py` 输出逐字节一致。
- HEX 没有 ELF 的调试符号、源文件路径和类型元数据；不得将分析命名说成原始符号恢复。

## 两个独立映像

| 区域 | 地址 | 静态证据 |
|---|---|---|
| 启动程序分区 | `0x08000000–0x08003FFF` | 45 项向量表，初始 SP `0x20001088`，Reset 向量 `0x080000C9`；运行时入口 `0x080000B4`；主函数候选 `0x08002CF4` |
| 应用分区 | `0x08004000–0x0800F7FF` | 第二套 45 项向量表，初始 SP `0x20001680`，Reset 向量 `0x080040CD`；运行时入口 `0x080040B4`；主函数候选 `0x0800A708` |
| 更新相关元数据候选 | `0x0800F800–0x0800FBFF` | 起始 halfword `0x3EC9`；`0x0800F804` 有 `app.bin`；`0x0800F828` 有 `0xC136` |
| 参数页候选 | `0x0800FC00–0x0800FFFF` | 前 96 字节包含整数参数，起始 `0x3EC9`、末尾 `0xC136`；具体字段待调用关系确认 |

以上是分析所选的分区范围，并非恢复出的链接器 section。两套向量表在各自基址的 `+0xB4` 立即进入 Thumb 代码，因此每表长度为 `0xB4`（45 个 word），不能按常见 48 项向量表直接覆盖后续指令。

启动程序跳转应用的直接证据：`0x08002E0E` 从 `0x08004000` 取栈顶，并校验 `(SP & 0x2FFFC000) == 0x20000000`；`0x08002E1C` 取应用复位向量；`0x08002E40` 执行 `MSR MSP, r0`；`0x08002E46` 执行 `BLX r0`。这比仅靠两个向量表推断 bootloader 更强。

长填充区：`0x08002F1B–0x08003FFF` 为零；`0x0800CF28–0x0800F7FF`、`0x0800F82A–0x0800FBFF`、`0x0800FC60–0x0800FFFF` 为 FF。零/FF 本身不证明这些地址永远不被读取或改写。

## MCU 与构建工具推断

两套表的保留槽、29 个外部中断位置与 ST 官方 STM32F030x8 表逐项匹配。复位入口使用 `LDR R0, SystemInit; BLX R0; LDR R0, __main; BX R0` 形态，也与 MDK-ARM 模板一致。这些字节证据说明 **STM32F030x8 兼容的向量/外设布局**，并很可能采用 **Keil/ARM 工具链**；它们不能识别实际芯片品牌。随后用户提供的 `主板.png` 经主分析者检查，芯片丝印为 **Geehy APM32F030C8T6**，板上晶振标注 **8 MHz**。因此实物判断应采用 APM32F030，而不是把布局匹配误认成 ST 芯片。Geehy 官方资料将该器件内核列为 **Cortex-M0+**。具体编译器版本以及原工程是否使用 STM32CubeMX 仍未知。

实物型号参考：[Geehy APM32F030x6/x8 官方数据手册](https://geehy.com/uploads/tool/APM32F030x6x8%C2%A0A%20version%20datasheet%C2%A0V2.0.pdf)。

兼容布局参考：[ST STM32F030x8 MDK 启动模板](https://raw.githubusercontent.com/STMicroelectronics/cmsis-device-f0/master/Source/Templates/arm/startup_stm32f030x8.s)、[ST STM32F030x8 CMSIS 头文件](https://raw.githubusercontent.com/STMicroelectronics/cmsis-device-f0/master/Include/stm32f030x8.h)。

按该型号的 IRQ 定义，非默认应用外设中断为：

| IRQ | 候选名称 | 应用处理函数实地址 |
|---|---|---|
| 7 | EXTI4_15 | `0x08005290` |
| 10 | DMA1_Channel2_3 | `0x08004FF4` |
| 11 | DMA1_Channel4_5 | `0x0800500C` |
| 13 | TIM1_BRK_UP_TRG_COM | `0x0800850C` |
| 27 | USART1 | `0x080094A4` |
| 28 | USART2 | `0x080094D8` |

启动程序非默认外设中断只有 IRQ10 (`0x08000220`) 和 IRQ27 (`0x080029E8`)。向量命中只表示 handler 地址不同，不证明外设一定被启用；需要继续核对初始化寄存器和调用。

## 字符串与复现

`strings.txt` 包含 784 个 ASCII/UTF-16LE 候选，大部分是指令字节偶然可打印。明确可读的文件名 `app.bin` 出现在 `0x080002EC` 和 `0x0800F804`。未发现可直接恢复工程名称、编译日期、原函数名的文本；此结论只覆盖脚本所采用的 ASCII/UTF-16LE 至少 4 字符扫描。

```sh
python3 recovery/tools/parse_hex.py stm32_fw.hex --output recovery/artifacts
arm-none-eabi-objdump -D -b binary -marm -Mforce-thumb \
  --adjust-vma=0x08000000 recovery/artifacts/firmware.bin
```

`objdump -D` 会把向量、literal pool、参数及填充也当指令，必须依据控制流区分代码和数据。`manifest.json` 保存身份、范围和限制；`vectors.csv` 同时列出两套表及带“候选”含义的 STM32F030x8 IRQ 名称。
