# 启动、Bootloader 与双镜像边界

这是根据原始 HEX 转换出的二进制和 ARM Thumb 指令手工还原的静态分析。`reconstructed/startup_boot.c` 是可读 C 逻辑译文，名称为分析者命名；没有原始调试符号，外部函数声明并不等于这些函数已恢复。已用 `arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -std=c11 -ffreestanding -Wall -Wextra -Werror -fsyntax-only` 校验语法；没有运行硬件或验证与原固件行为等价。

## 实物识别修正

用户后补的 `主板.png` 照片由主分析者读出主控丝印 **Geehy APM32F030C8T6**，晶振 **8 MHz**。按 Geehy 该型号资料，其内核为 **Cortex-M0+**；这里不把 STM32F0 兼容寄存器布局当作实物厂商证据。下文 STM32F0 只表示指令/寄存器布局对照。初次语法检查使用 `-mcpu=cortex-m0` 是覆盖本译文所用基础指令的保守检查，不表示芯片实际为 Cortex-M0。

## 两个独立镜像（直接证据）

|项目|Bootloader|Application|
|---|---|---|
|向量表地址|0x08000000|0x08004000|
|初始 MSP|0x20001088|0x20001680|
|Reset 向量值|0x080000C9|0x080040CD|
|实际 Reset 指令|0x080000C8|0x080040CC|
|SystemInit-like|0x0800253A，仅 `BX LR`|0x08008508，仅 `BX LR`|
|运行时入口|0x080000B4|0x080040B4|
|scatter-loader|0x080001D8|0x08004530|
|main|0x08002CF4|0x0800A708|
|默认 IRQ handler|0x080000DA|0x080040DE|

两个向量表各有 45 个 32-bit 项，0xB4 偏移开始已是指令，不应把后面的 3 项误记成 IRQ。Boot main 在 0x08002E0E 起直接加载 0x08004000/04，检查栈地址，执行 `MSR MSP` 后 `BLX` 应用 Reset，证明这不是仅靠相似布局猜测的双镜像。

## 运行时内存初始化（直接证据）

Boot scatter table 位于 `0x08002ED4..0x08002EF4`：

1. 从 `0x08002EF4` 复制 0x28 字节至 `0x20000000`，函数 `0x08002CD4`。
2. 从 `0x20000028` 起清零 0x1060 字节，函数 `0x08002CE4`。结束地址为 `0x20001088`（不含）。

App scatter table 位于 `0x0800CE78..0x0800CE98`：

1. 从 `0x0800CE98` 复制 0x90 字节至 `0x200000B4`，函数 `0x08009630`。
2. 从 `0x20000144` 起清零 0x153C 字节，函数 `0x08009640`。结束地址为 `0x20001680`（不含）。

这些尾地址不代表物理 SRAM 总容量，也不能据此确定栈的独立大小。App 特意保留了 SRAM 开始的 0xB4 字节。

App main 的 `0x0800A708..0x0800A740` 将 45 个向量从 `0x08004000` 复制到 `0x20000000`，随后置 `RCC[0x18].bit0`，将 `0x40010000` 低两位改为 3。按 STM32F0 寄存器布局，这对应 SYSCFG 时钟及 SRAM 映射到零地址。原始寄存器写入可以直接确认；该布局与 STM32F030x8 兼容；实际型号以照片识别的 APM32F030C8T6 为准。

## Boot main 完整顶层逻辑

`0x08002CF4` 的初始化顺序：HAL-like 初始化 `0x08001038` → 时钟 `0x080024C4` → GPIO `0x0800215C` → DMA `0x08002134` → I2C1 `0x080021B4` → USART1 `0x0800220C` → 开启 512-byte 接收（`0x0800175C`，handle=0x20000BA0，buffer=0x2000099C）→ 检查/初始化 Boot metadata `0x08000280`。

1. `0x08000A7C` 读取 `0x48000410` 的 bit0。低电平且 Flash `0x0800F802 != 0xAAAA` 时，写入 0xAAAA。按 STM32F0 布局这是 PB0 输入。
2. 只有 `0x0800F802 == 0xAAAA` 才进入升级等待/通信循环；否则直接尝试启动 App。
3. 等待循环最长 **300 个软件秒，约 5 分钟**。`0x20000010` 不是毫秒 tick：SysTick handler `0x08002494` 每当 HAL tick 差值达到 1000 才加一。HAL tick 位于 `0x20000020`，增量位于 `0x20000018`（初值 1）。这是基于标准 SysTick 时基配置的静态推导，实际墙钟时间未测。
4. 收到数据标记 `0x20000B9E == 1` 时，调用 `0x080029F8(buffer, U16(0x20000B9C))`，随后清标记。
5. `0x20000005 == 1` 时退出等待并尝试启动 App。
6. `0x20000003 == 1` 时清标记、暂停接收、调用 `0x08002314`，再重启 512-byte 接收。该调用与升级接收路径有关，内部协议需另行分析。

三个 byte 倒计时位于 `0x20000000..02`，按软件秒递减。仅第 0 项在进入循环时设为 6；第 1/2 项由其他处理代码启动，不能认为它们从开机开始自动周期运行。到期处理如下：

|索引|调用|帧 command|payload|重装倒计时|
|---|---|---|---|---|
|0|0x08002E96|0x3C|0x18|10 秒|
|1|0x08002E80|0x3D|0x00|35 秒|
|2|0x08002EAC|0x3F|0x20000004 的 byte 值|10 秒|

发送函数 `0x08002A68` 的帧布局是 `[0xAA, payload_length+3, command, 0x01, payload..., XOR]`。XOR 覆盖索引 1 到 payload 末尾，不包括帧头。它调用 `0x08001CB8` 发送 payload_length+5 字节，timeout=5000。上述三个调用均 payload_length=1。

## Flash metadata

`0x08000280` 检查 `U16(0x0800F800) == (U16(0x0800F828) XOR 0xFFFF)`。不满足才写默认值，次序为：

- 0x0800F804：8 字节 `app.bin\0`。
- 0x0800F824：4 字节零。
- 0x0800F800：0x3EC9。
- 0x0800F828：0xC136。

0x0800F802 的升级标记与上述 magic 互补对独立。当前样本中 F800=3EC9、F802=FFFF、F828=C136，因此当前 metadata 是有效的，且没有已置位的 0xAAAA 升级请求。PB0 电平仍可能在启动时改变这个决定。

## App 交接细节与边界

`0x08002E10..0x08002E1A` 仅检查 `(app_sp & 0x2FFFC000) == 0x20000000`。后续顺序：保存 App Reset 地址 → 清 SysTick CTRL.TICKINT → 禁中断 → I2C1 GPIO/时钟清理（0x08000F8C）→ UART 清理（0x08001AD8）→ 写 NVIC ICPR=0xFFFFFFFF → 开中断 → 加载 App MSP → BLX App Reset。未见独立的 Reset 地址范围/Thumb-bit 检查。App 无效或返回时，在 `0x08002E48` 无限循环。

将该逻辑真正移植到可刷机 C 工程时，MSP 更新/跳转必须实现为专门汇编 trampoline；手工译文中的 `cpu_load_msp_and_blx` 仅表达原始指令语义。当前任务未执行任何 Flash 擦写或目标代码。

## 编译器线索

相同的 scatter-loading table + 16-byte descriptor + ARM runtime 除法/内存例程，以及 0x080095D2 周边的 switch helper，是 ARM/Keil 工具链风格线索。仅据此不能确认具体 ARMCC/Keil 版本，也不能恢复原始工程配置。
