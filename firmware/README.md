# 日常开发入口

采用 C11、固定内存、现有裸机调度的渐进架构。无需运行反编译器或完整 CPU 模型即可开发、测试纯 C 模块；原完整汇编作为兼容实现继续提供尚未迁移的功能。

| 路径 | 职责 |
|---|---|
| `include/charge/` | 公开 API、状态类型、前置条件 |
| `src/domain/` | 通道、计时和参数规则，不依赖外设 |
| `src/protocol/` | 组帧、校验、解析事件，不直接发送 UART |
| `src/services/` | I²C 存储分页及升级 CRC；存储通过回调访问设备 |
| `platform/apm32/` | 原 RAM 布局、驱动调用、专用 ABI、Flash 链接布局 |
| `tools/prepare_legacy.py` | 从只读恢复源码生成兼容汇编，只写 `build/` |
| `platform/apm32/migration.json` | 原生替换的入口、ABI、状态、调用点和验证契约 |
| `../tests/` | 行为测试、原始 HEX 差分、原生集成与架构约束 |

在仓库根目录执行 `make host` 构建 `firmware/build/libcharge.a`，或 `make native` 生成完整 64 KiB 开发固件。`make verify` 包括所有新工程验证。需要系统 C 编译器、Make、Python 3.9+、GNU Arm Embedded GCC/binutils；差分测试的 Python 依赖见根目录 `requirements-dev.txt`。完整旧恢复检查还需要 Capstone。

新 C 代码真正被链接并从旧入口调用：参数转换、发送帧构造、通道启停/清理以及 I²C 读/等待/分页写。新代码使用 App 内 `0x0800D000–0x0800F7FF`，Boot、原 App 入口、元数据和配置页保留。链接器拒绝超区以及新的 `.data/.bss`，因为旧启动尚不负责初始化新静态变量。开发固件没有烧录目标，也不输出未经验证的升级 `app.bin` 包。

日常新增规则放入相应 C 模块，状态由调用者持有；外设副作用通过接口表达。只有平台层允许使用绝对地址。改变协议、时间语义或持久化布局时先更新明确的契约与测试。每个新的原生替换都需要检查原调用者的实际寄存器使用，不能只凭 C ABI 猜测。

`recovery/reconstructed/*.c` 是历史阅读证据，不是第二份需要同步编辑的开发源码。不要修改恢复汇编来迭代新规则，也不要将 CPU 模型打包到 MCU。未迁移的主循环、复杂业务、IRQ/DMA、设备输出及 Boot 仍由兼容层负责，详见[架构说明](../docs/architecture.md)。

协议 API 的解析缓冲必须由调用者提供 256 字节；该 API 返回事件时已重置解析索引。它尚未接入原生 RX，因为原全局缓冲与相邻对象的边界、回调重入和中断时序需要单独处理。不要直接把旧 `0x20001024` 地址当作满足此 API 的新缓冲分配。

首次台架验证应核对串口/存储、通道状态、IRQ 并发、最深栈与上电/升级流程，按[验收记录](../docs/verification.md)补证。主机和指令差分通过不代表这些硬件条件已验证。

新增原生替换先登记迁移契约，再修改实现与独立差分场景。`make native` 会校验契约与链接布局、平台符号、已分类调用点及验证文件的一致性；结构检查不替代原 Thumb 行为验证。详见[迁移契约与验证运行](../docs/design-docs/migration-contracts.md)。
