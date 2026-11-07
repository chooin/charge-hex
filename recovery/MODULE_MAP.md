# 代码阅读地图

这里的名称是按机器码作用整理的分析名称，不是原工程目录或原符号。所有地址都是原 Flash 地址。整机可构建源码在 `full_assembly/firmware.S`；C 反编译稿保留同地址文件名，人工整理版本在 `reconstructed/`。

## 建议的阅读顺序

| 模块/入口 | 原地址 | 建议先读 |
|---|---|---|
| Boot Reset、内存初始化 | `080000C8`、`080001D8` | [startup_boot.c](reconstructed/startup_boot.c) |
| Boot main、应用交接 | `08002CF4` | [startup.md](notes/startup.md) |
| YMODEM-like 整个文件接收 | `08002AE8` | [原函数 C 稿](decompiled/functions/0x8002ae8.c)、[升级说明](notes/update_protocol.md) |
| 单包接收、CRC、Flash 提交 | `08002250`、`080001FC`、`08002314` | [firmware_update.c](reconstructed/firmware_update.c) |
| App Reset 与 runtime | `080040CC`、`08004530` | [startup_boot.c](reconstructed/startup_boot.c) |
| App 初始化和完整主循环 | `0800A708`、循环段 `0800A7D4` | [application_main.c](reconstructed/application_main.c)、[控制流说明](notes/application_main.md) |
| 串口完整块校验 / 逐字节解析 | `08008E84` / `08008EAC` | [serial_protocol.c](reconstructed/serial_protocol.c) |
| 协议命令分派 | `0800B0DC` | [business_handlers.c](reconstructed/business_handlers.c) |
| 标识符相关状态处理 | `08009694` | [business_handlers.c](reconstructed/business_handlers.c) |
| 参数载荷转换 | `0800BCD8` | [serial_protocol.c](reconstructed/serial_protocol.c)、[协议字段表](notes/protocol.md) |
| 较大的通道状态处理 | `0800C298`、`0800BE24` | [C298 C 稿](decompiled/functions/0x800c298.c)、[BE24 C 稿](decompiled/functions/0x800be24.c)；业务字段物理含义仍有未知 |
| 通道位图 → 移位输出 | `0800C85C` → `08007474` / `08007400` | [application.c](reconstructed/application.c) |
| I²C 存储读/就绪轮询/分页写 | `08007498` / `080074C4` / `080074FC` | [application.c](reconstructed/application.c) |
| 显示字节输出 | `0800882C` | [application.c](reconstructed/application.c) |
| PB10 脉宽命令输出 | `0800CDB8` | [application.c](reconstructed/application.c) |
| GPIO/ADC/TIM/UART 初始化 | `08007DE8` / `08007D44` / `08007FC4` / `08008034`、`0800806C` | [外设分析](notes/application.md)、[全函数索引](decompiled/README.md) |
| USART1 / USART2 IRQ | `080094A4` / `080094D8` | [向量表](artifacts/vectors.csv)、同地址反编译文件 |

## 关键 RAM 布局

| 原地址 | 已观察用途 | 限制 |
|---|---|---|
| `20000000–200000B3` | App 的45项重定位向量 | Boot 阶段这一区间用途不同 |
| `200000B8` | 通道位图 | 外部输出取16位，低12位对应通道 |
| `200000DD–200000DF` | 12路双位状态码 | `01/10` 与调用零/非零对应 |
| `200005E4` | 12个、每个52字节的通道记录 | 测量/计费等字段单位尚未全部命名 |
| `20000854` | 全局模式和参数区 | 不是一个已完整找回类型名的原始 C struct |
| `200008D4` | 93个 uint16 软件计时槽 | 到期分派见主循环；时间单位依赖时基路径 |
| `20000C10` / `20000E14` | 两路512字节接收缓冲 | DMA和IRQ并发需要硬件或完整外设模型验证 |
| `20001024` | 逐字节组帧缓存 | 不能从测试用的256字节模拟缓存推断原分配大小 |

## 如何理解不同 C 文件

- `decompiled/functions/` 是所有已识别函数的 Ghidra 输出，便于快速阅读，保留类型和跳转分析警告。`undefined`、`extraout_r1` 等是反编译器尚未完整推断的类型/调用约定，不是原始变量。
- `reconstructed/` 是重点逻辑的整理版。`application_main.c` 使用显式 CPU 上下文，其他文件多用原地址的寄存器或内存访问。它们之间有重复说明性实现，并非已经整合好的 SDK 工程。
- 完整固件构建以 `full_assembly/` 为准。它保留了所有程序、常量和配置字节，没有把剩余驱动换成空函数或成功返回值。

任何重命名为“电流”“余额”“卡号”等具体业务字段的工作，都应再与板级接线和真实输入/串口记录对照，避免把可执行代码整理成含义错误的源码。
