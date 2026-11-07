# Bootloader 升级协议与 Flash 提交

实物主控是用户照片识别的 Geehy APM32F030C8T6（Cortex-M0+）。以下地址及分支来自本 HEX 的 Thumb 指令，函数名是分析命名。协议规则也与 [ST 官方 YMODEM IAP 实现](https://github.com/STMicroelectronics/STM32CubeF7/blob/master/Projects/STM32F769I_EVAL/Applications/IAP/IAP_Main/Src/ymodem.c) 中 SOH/STX、序号互补、CRC、控制字符结构相符；这是识别为 YMODEM 的依据，不代表固件直接来自该仓库或使用 ST 芯片。

已增加 `reconstructed/firmware_update.c`：CRC16、单包接收、Flash 单页更新、接收完成后的提交逻辑。完整文件接收状态机 `0x08002AE8` 和 I2C/HAL 底层仍保留外部声明，未冒充全部还原。

## 两阶段更新路径

```text
自定义 AA 命令 3E/payload=0
        ↓ 置 RAM[20000003]=1
Boot main 暂停 DMA 接收，进入 08002314
        ↓
08002AE8 / 08002250 接收 YMODEM 文件
        ↓ 08001DF0
I2C 0xA0（7-bit 0x50）的 EEPROM-like 器件暂存
        ↓ 全文件接收成功
08002314 逐 1024 字节读回（08001D90）
        ↓ 0800042C
逐 1024 字节页更新 App Flash（08004000 起）
        ↓
更新 F804 文件名、F824 长度、F802=5555，准备报告结果
```

I2C 设备使用 16-bit 内存地址、128-byte 写页、写后轮询；可寻址 64 KiB。这与 24C512 类 EEPROM 特征相符，**没有仅凭代码确认实际器件型号**。

## 自定义升级控制帧：0x080029F8

该函数检查 `XOR(buffer[1..length-2]) == buffer[length-1]`，再根据 byte2 command 分发。本函数未额外验证帧头、byte1 声明长度或最小包长；上游接收边界需要结合串口模块，不能假设它自身做了这些校验。

|command|已确认动作|
|---|---|
|0x3C|payload byte4 等于 0x18 时设 timer1=1；否则设 status=3、timer2=1；总会清 timer0|
|0x3D|清 timer1|
|0x3E|payload=0 时置启动接收标记 0x20000003=1；非零则写入 status 并设 timer2=1|
|0x3F|置退出等待标记 0x20000005=1，清 timer2|

timer0..2 位于 0x20000000..02，status 位于 0x20000004。Timer2 到期发送 `AA/.../3F/01/status/XOR`，收到 3F 响应后 Boot main 才退出等候并尝试跳 App；更新提交函数本身不立即跳转。

## YMODEM 包：0x08002250、0x08002AE8

`0x08002250` 首字节控制：

|首字节|解释/行为|
|---|---|
|01|128-byte 数据块|
|02|1024-byte 数据块|
|04|EOT，长度返回 0|
|18 18|对端取消，长度返回 2|
|41 或 61|A/a 取消，状态返回 2|
|其他|无效状态 1|

RAM 接收缓冲区 `0x20000448` 有一个非线上 padding byte：索引0=控制字节，索引1未用，索引2=块序号，索引3=序号反码，索引4起=payload，之后为 CRC 高/低字节。SOH/STX 后再接收 payload_size+4 字节。检查序号互补与 payload CRC 后才返回有效数据长度。

CRC 位多项式为 `0x1021`，函数 `0x08002AC4`；全块计算 `0x080001FC` 最后补两个零字节，等价于 CRC-16/XMODEM（init=0，无反射、xorout=0）。恢复 C 的纯 CRC 函数已编译成宿主库，与 Python `binascii.crc_hqx(...,0)` 交叉验证，覆盖空输入、`123456789`（31C3）、128-byte 和 1024-byte 块。脚本：`verification/check_update_crc.py`。仅执行了纯 CRC；所有硬件依赖链接成 trap，未执行固件硬件操作。

`0x08002AE8` 的文件级行为：

- 调包接收时 timeout=5000。回 ACK=06、NAK=15、CAN=18、CRC request='C'=43。
- 初始块序号为0。头块提取最多32字节文件名到 `0x20000428`；随后读取文件长度文本，交 `0x0800245C` 做十进制转换。
- 有效十进制声明长度 **大于 0xB801（47105）** 时，发两次 CAN，返回状态5。注意不是 `>=0xB800`；源代码重建应保留这个真实边界。转换函数成功状态未被检查。
- 数据块序号不等于预期则发 NAK；数据写到暂存设备当前偏移，由 `0x08001DF0` 进行分页写入，成功 ACK，并推进偏移与8-bit块序号。
- EOT 回 ACK，准备下一个头块；文件名为空的尾部块回 ACK 并结束会话。
- 暂存写失败回两次 CAN，结果4；取消路径结果2。超长结果5。
- 接收累计写偏移在调用 I2C 写时取低16位；单次写有64KiB边界检查，但文件级未见累计长度等于声明长度的最终校验。正常单文件恢复必须正确生成长度、块序号和尾包，不应把未覆盖的异常输入称作兼容。

## 暂存设备访问

- `0x08001D90(offset, buffer, bytes)`：检查 bytes <= 65536-offset，使用 I2C handle `0x20000850`、设备地址 A0、16-bit 内存地址读取，timeout=1000。
- `0x08001DF0(offset, buffer, bytes)`：同样检查边界，按128-byte页边界拆分写入，timeout=500。每次写后调用 `0x08001DBC` 轮询设备就绪，计时边界约50个 HAL tick。
- 这是升级中间存储；收到数据包时尚未开始替换 App Flash。

## Flash 写入与擦除范围

`0x0800042C(address, data, halfwords)`：

1. 检查 `(uint32_t)(address - 0x08004000) < 0xBBFF` 且 address 为偶数。
2. 将 address 所在的 **1 KiB 页**（address & ~0x3FF）原内容复制到 SRAM `0x20000028`。
3. 在 SRAM 页副本中覆盖指定 halfwords。
4. `0x08000300(page,1)` 擦除此页，再用 `0x08000794` 逐 halfword 写回完整512个 halfword。

因此该函数接受的偶数起始地址是 **0x08004000..0x0800FBFE**；保护了起始16KiB Boot，且排除了 **0x0800FC00** 参数页。更新 metadata 的 **0x0800F800..FBFF** 页仍在允许范围中。它不是整个芯片 mass erase。

原函数仅检查起始地址，没有额外检查 halfwords 是否超过当前页剩余长度。已还原的正常调用均为整页对齐或短 metadata 更新；不能将其推广为安全的任意范围写 API。

## 提交函数：0x08002314

返回0时：按声明文件大小，先处理完整1KiB块，再处理尾块；目标起点 `0x08004000`。每块调用暂存读取 `0x08001D90` 后直接调用 Flash 更新 `0x0800042C`。

尾块 halfwords 参数取 `remainder >> 1`，所以 **奇数字节文件的最后一字节不会被新数据覆盖**。如果声明长度恰为0xB801，完整 App 区有0xB800字节，最后剩余1字节在 F800 页对应的写计数为0：该函数仍会擦写并恢复这整页。已重建 C 保留该细节，未偷偷修正算法。

成功后：

- 写文件名至 `0x0800F804`，写入字节数按偶数边界包含终止零（最多32字节规则）。
- 写文件长度 uint32 至 `0x0800F824`。
- 写 marker `0x5555` 至 `0x0800F802`。
- status=0，timer2=1。

结果2/4/5时：写 marker `0xA5A5`，status分别6/5/4，timer2=1。其他结果直接返回。

重要的恢复边界：提交阶段未检查暂存读取结果；Flash 更新助手也未将擦除/编程结果返回给上层。文件尾部之外保留旧 Flash 内容；未见完整新镜像校验或事务回滚。以上是原指令行为陈述，不代表已实际触发失败。

## 验证和未恢复部分

新增 C 已以 `-mcpu=cortex-m0plus -mthumb -std=c11 -ffreestanding -Wall -Wextra -Werror -fsyntax-only` 通过。CRC交叉验证通过。尚未做 UART 输入回放、板上升级、I2C器件读取或 Flash 写入。仍需恢复/替换完整接收状态机、I2C/UART/Flash底层，以及确认真实硬件引脚和器件，才能构建可刷机工程。

CRC 另已用 Unicorn 执行原固件 `0x080001FC`，对同样5组输入与实际编译后的恢复 C 和 Python `crc_hqx` 三方比较，全部一致；结果见 `verification/update_crc_result.json`。这不扩展到升级状态机或硬件验证。
