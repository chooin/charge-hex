# 全部已识别固件指令的 C 语义模型

此目录将 `full_assembly/instructions.json` 中的 **21069 条 Thumb 指令、44750 个指令字节**全部翻译为可编译 C 运算和控制流标签。1301 个 BL 调用点均在同一模型内部继续执行被调代码，BX/BLX/POP PC 经显式地址分派；没有把库函数或驱动替换为空实现。

它是 **host 可构建的完整静态 C 语义模型**，不是原始高层源码，也不是能直接装进64 KiB Flash的MCU C工程。完整可重建的MCU固件见 [`../full_assembly/`](../full_assembly/README.md)；按函数阅读的反编译稿见 [`../decompiled/`](../decompiled/)。

## 文件和构建

- `firmware_model.c`：明确的C运算、寄存器/APSR效果、分支和调用；每条原指令地址都保留为标签和注释。
- `firmware_model.h`：CPU、RAM、Flash、总线和事件回调接口。
- `firmware_data.c`：完整65536字节Flash的**数据表示**，供向量、literal pool、CRC及固件自读使用；执行路径来自编译后的C，不解释这些字节中的opcode。
- `generate.py`：以已核对二进制和汇编指令清单重新生成上述文件。
- `coverage.json`：指令数量、助记符、来源hash及覆盖边界。
- `verify.py` / `verification.json`：C与原始Thumb的差分验证。

在仓库根目录：

```sh
make -C recovery/full_c
make -C recovery/full_c demo
make -C recovery/full_c verify
```

`all` 用系统 C 编译器严格编译并生成 `build/libfirmware_model.a`。`demo` 从真实复位向量开始运行，没有注册外设响应，因此运行4289条指令后明确返回 `-2`，故障地址为 `0x40022000`（Flash控制寄存器访问），PC为 `0x0800103C`。这证明复位路径已在C中执行，同时也清楚显示尚未建立的设备边界。

`verify` 当前使用 macOS 的 `-dynamiclib` 构建测试库，并需要已安装的 Python Unicorn/Capstone。静态库构建本身采用标准 C11。

## API 使用

```c
uint8_t ram[8192] = {0};
FwMachine m;
recovered_firmware_init(&m, ram, sizeof ram);
/* 如需越过外设边界，明确实现并注册 m.bus_read / m.bus_write。 */
int status = recovered_firmware_run(&m, 100000);
```

`r[0..14]` 保存通用寄存器、SP和LR；`pc` 是下一条执行的真实固件地址；`apsr` 保存NZCV；`primask` 保存CPS效果。可设置 `stop_address` 停在指定地址，或使用有限指令预算运行并续跑。

总线回调必须实现实际需要的设备含义，例如RCC、UART、GPIO、Flash控制器、NVIC/SysTick和零地址映射。没有回调时未映射访问会失败，不会返回假成功。内建Flash指针只供读；若实验需要可变Flash数据，可让它指向调用方的可变备份，并由总线写回调维护。但**被翻译的指令固定属于当前固件**，写入新程序不会自动重编译C控制流，不支持任意自修改代码。

DSB/ISB作为显式事件通知；该单线程模型本身没有排队的总线事务。CPS修改PRIMASK；MSR MSP按字对齐更新SP。异常入口、自动压栈/退栈、IRQ调度、DMA、周期精确时序和设备模型不在此CPU译文中实现。遇到EXC_RETURN立即显式失败，不能拿这份模型当作整块主板仿真器。

| 返回码 | 含义 |
|---:|---|
| 0 | 指令预算用完，可续跑 |
| 1 | 到达 `stop_address` |
| -1 | PC不在已识别指令清单中 |
| -2 | 总线访问未建模，或回调报告故障 |
| -3 | BX/POP要求Thumb目标却得到偶地址 |
| -4 | 遇到尚未建模的异常返回 |
| -5 | 非对齐半字/字访问；报告错误，不自动进入HardFault |

## 已完成的验证

`verification.json` 记录最终源文件hash和结果：

- 对**全部21069个指令地址**各做2组受约束CPU状态，共 **42138组单指令差分**，全部通过。比较寄存器0..14、PC、NZCV、PRIMASK及全部64 KiB测试RAM。
- **1354组完整函数执行**，覆盖两份无符号除法、CRC、全部8位通道参数/4种启停值、通道清理、内存复制/清零。嵌套调用、栈和switch helper实际执行，不使用函数stub。
- 未分类PC、缺失总线、非Thumb目标、异常返回四类显式失败边界通过测试。另有18组独立非对齐访问测试，以及LDM/STM/POP三组“保留首次故障、停止后续总线访问”测试。
- 64 KiB测试RAM用于观察边界和栈效果，不代表实物SRAM有64 KiB；主板型号对应8 KiB。

单指令输入限制为已映射且按访问宽度对齐的数据地址、有效Thumb跳转目标、字对齐MSP。测试不是对全部可能状态的形式化证明，未检验异常时序或硬件行为。全程序启动仅验证到上述第一个外设边界。

对齐规则按 [Arm Cortex-M0+ Devices Generic User Guide, DUI0662A §3.3.4](https://documentation-service.arm.com/static/5f04aadfdbdee951c1cdc957?token=) 单独实现：半字需2字节对齐、字/多字需4字节对齐，违规应产生HardFault。当前Unicorn的MCLASS模式允许这些非对齐访问，因此此边界不以Unicorn为判据；模型在任何总线调用前返回`-5`。

一旦内存访问或总线回调设置故障，后续同指令的读写会短路，保留首次`fault_address`和故障指令`pc`；例如LDM/STM/POP不会继续发出总线调用。**不模拟精确异常的完整寄存器状态或回滚**：发生故障前/同条复合指令中的寄存器更新可能仍可见，不会自动压栈进入HardFault处理器。MSP非对齐输入也不拿Unicorn结果当架构判据；有效MSP输入限制保持字对齐。

覆盖范围依赖已识别指令清单，未分类数据字节没有被悄悄当成代码。动态跳到未分类地址会明确失败。不能把“21069条已识别指令全部有C语义”改写成“原始C项目和所有硬件行为已百分之百恢复”。

独立复核另见 [review.md](review.md)。`python3 recovery/full_c/review_boundaries.py` 在独立临时目录编译最终模型，并对移位0/31/32/33/255等边界、进位/借位和全部16种初始NZCV组合执行3584组对照，全部通过；结果及源文件摘要保存在 `review_boundaries.json`。
