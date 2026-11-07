# 重构验收记录

日期：2026-11-07；恢复基线：`f3451ef`；本次变更未提交。原始 HEX 文本 SHA-256 保持 `22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf`。

环境：macOS ARM64，系统 Clang、GNU Arm GCC/binutils、Python 3，Unicorn 2.1.4、Capstone 5.0.7。未连接或烧录主板。

## 结果

下列十项中，开发层/既有恢复验证 **8 项通过、0 项失败**；整机板级验证与全量纯 C 迁移 **2 项未知/未完成**。不能把后两项计为通过，也不能将局部差分结果推广成全部固件等价。

| 项 | 命令 / 证据 | 结果及范围 |
|---|---|---|
| BASELINE-01 原恢复基线 | `make -C recovery verify` | 通过；包含64 KiB字节一致性及既有全部恢复检查。运行只产生3个elapsed字段变化，已去除时间噪声；恢复源码与结果内容不变 |
| BUILD-01 模块与原生构建 | `make` | 通过；严格C11主机库、Cortex-M0+交叉编译、独立链接ELF/BIN/HEX；无新增静态RAM |
| ARCH-01 依赖约束 | `tests/check_architecture.py` | 通过；纯模块不含硬件地址、旧ABI、平台导入、堆分配；原HEX摘要正确 |
| PROTO/CONFIG | `tests/protocol_test.c`、`tests/protocol_differential.py` | 通过；76,704个字节步骤、256发送长度、256标识符模式、600参数、512块校验。对照直接来自原HEX |
| CHANNEL/TIMER | `tests/test_domain_services.c`、`tests/check_domain_services.py` | 通过；1,024通道状态、12记录清理差分；timer回绕/零值/到期主机行为测试。未替换整个调度器 |
| STORAGE/CRC | 同上 | 通过；66 CRC、43存储差分，分页数据和I/O顺序、读写错误、重试、超时边界、tick回绕；另有主机边界及ASan/UBSan验证 |
| NATIVE-01 镜像与入口 | `tests/check_native.py` | 通过；1,642原生场景，七入口确实执行新ARM C扩展；比较内存及I/O轨迹、标准ABI、clear的r3、read的r1/r2、部分shim的ip，实际8 KiB SRAM映射 |
| NATIVE-02 实际调用链 | 同上，6个`9D84`场景包含在1,642项中 | 通过；原通道初始化函数真正调用新clear/set，覆盖清理后经r3访问的非标准约定 |
| BOARD-01 整机硬件 | 尚无主板运行证据 | 未知；需测IRQ/DMA并发、电气时序、最深栈、上电与升级、外接设备 |
| MIGRATION-01 全量高层C | 架构文档的剩余归属 | 未完成；Boot、复杂主循环/业务及大部分驱动仍运行兼容汇编。它们保留实现，但没有宣称已转换成常规C |

## 验证范围和可复现性

`make verify` 运行新工程构建、所有主机测试/差分以及原生验证。原生验证报告自动写入 `firmware/build/native_verification.json`，附当前代码/测试/构建文件摘要和新固件摘要；该生成文件忽略提交，运行后可检查是否对应当前源码。`make verify-recovery` 继续提供原恢复工程的完整独立复验入口。

新原生镜像共64 KiB，修改只能落在7个入口的16字节窗口或 `0xD000–0xF7FF`。Boot、所有未替换代码/数据、metadata/config保留；BIN与新HEX解码内容相等。新镜像和原始HEX之间有有意差异，不能再使用原固件摘要判定新镜像通过。

差分中的 UART/I²C/tick/刷新调用在设备边界截获，对照参数、数据、错误和顺序。交付固件内保留真实旧驱动，测试截获不进入固件。CPU仿真未提供实际设备、电气响应、中断调度或周期精度。主机parser测试使用256字节缓冲；没有借此扩大原板缓冲的已知分配。

默认保持有效输入业务契约。新API的容量/NULL/缺失回调拒绝属于新增调用边界；未把它推广为原协议整体加固。旧主循环入口、回调观察状态和旧静态RAM分配仍有自身约束。

复核中发现并修正了ABI判断：旧函数push的r3槽可能被参数/临时值覆盖，不一定保存入口r3。最终检查只比较已证实的寄存器契约，并加入真实上游调用者验证。源码和验证结果均以修正后的实现为准。
