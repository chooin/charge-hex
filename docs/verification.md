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

## Logic compatibility follow-up (2026-11-08)

The owner requires original behavior to remain unchanged even when compiled bytes
differ. This follow-up audits the seven native replacements against the immutable
original HEX, repairs concrete counterexamples, and expands repeatable verification.
The earlier record above remains historical evidence. This run is based on commit
`d09d40f` plus the local compatibility/test changes described here.

### Counterexamples and fixes

| Native entry | Previous discrepancy | Compatibility change |
| --- | --- | --- |
| Channel state `0x0800C85C` | Register channel=256, enable=1 changes channel 0 in the original but was ignored by the new entry | Explicit modulo-256 channel conversion; test full 32-bit enable before narrowing |
| Storage write `0x080074FC` | Address=`0xFFFF0000`, size=65664 with second write failure: original attempts two 128-byte chunks and returns 1; new code attempted one and returned 0 | Preserve full-register range arithmetic, original page/tail masks, address wrapping and failure propagation in the native adapter |
| Storage read/write | Nonempty NULL transfers were rejected before reaching original driver validation, losing handle error writes or changing raw read status | Exceptional native calls execute the original validation paths; ordinary calls retain portable services |
| Frame send `0x0800C7C4` | Original can read a nonempty payload from mapped address zero; portable NULL rejection suppressed native output | A small assembly byte-load helper preserves machine reads without a C NULL dereference |

Raw native clear/config/frame signatures also now express full-register behavior:
unsigned wrapping clear-address arithmetic, endian exactly equal to 1, and length
rejection before byte-field conversion. The public portable APIs and their existing
validation contracts have not been weakened. Implementations are in
[legacy_bridge.c](../firmware/platform/apm32/legacy_bridge.c) and
[abi_shims.S](../firmware/platform/apm32/abi_shims.S).

### Fresh results

`make native` rebuilt the changed ARM image; the final `make verify` exited 0.

| Check | Result | Scope |
| --- | --- | --- |
| Existing host, architecture and portable differential suites | PASS | Includes 76,704 parser byte steps and existing domain/service cases |
| Existing native suite | PASS, 1,642 cases | Layout, seven C entries, caller ABI and I/O effects |
| [Native edge suite](../tests/check_native_edges.py) | PASS, 5,884 cases | 128 page offsets, timeout 499/500/501 and wrap, errors/partial reads, config thresholds, raw register regressions, real callers |
| [Native sequence suite](../tests/check_native_sequences.py) | PASS, 20,376 cases | Packed states, persistent sequences, all 4,096 channel-reset masks, raw register conversions, frame boundaries/fields, zero-address payloads and real identifier caller |

The three native suites total **27,902 paired execution cases**. The edge suite
includes 38 cases that execute real I²C driver validation/busy/locked prefixes and
check their handle side effects; most device bodies remain scripted boundaries.
Both new suites are part of the root `make verify` target. Input/source and image
hashes are captured, and assertions reject inputs changing during a run.

All **559 classified original instructions** in the seven replaced functions were
executed at least once across the extended suites:

| Original function | Executed / classified instructions | Static direct callers reviewed |
| --- | --- | --- |
| Storage read `7498` | 19 / 19 | 2 |
| Storage wait `74C4` | 22 / 22 | 3 |
| Storage write `74FC` | 102 / 102 | 2 |
| Channel clear `9E14` | 12 / 12 | 4 |
| Configuration `BCD8` | 144 / 144 | 2 |
| Frame send `C7C4` | 37 / 37 | 11 |
| Channel state `C85C` | 223 / 223 | 10 |

This is instruction coverage, not proof of every input, path combination or schedule.
Static review covered all 34 classified direct call sites and found no additional
live-register dependency beyond the existing shim contracts. No classified direct
branch or raw 32-bit pointer into an overwritten entry interior was found. Known
frame/config callers supply disjoint payload buffers. Dynamic call targets remain
outside the completeness claim.

### Artifact identity and reproduction

- Original HEX SHA-256 remains
  `22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf`.
- Fixed native BIN SHA-256 is
  `654e16eeb7b19c2b95835c656eefc09b640eaac5fd986abdb30694befdb87611`.
- The new BIN and HEX represent the same 65,536 Flash bytes. There are 1,548
  intentional differences from the original, confined to the seven entry windows
  and C extension. Boot, metadata and configuration bytes remain unchanged.
- The earlier byte-identical recovery BIN remains
  `3016dafb97375b22cdb49f1ed41b05c7f1aa940d58c5ce42c2fdbe682245a144`.

Generated evidence is under `firmware/build/`: `native_verification.json`,
`native_edges_verification.json`, `native_sequences_verification.json`, and
`logic-review/verification.log`. These outputs are local build artifacts.
REA/Ghidra additionally re-analyzed original configuration entry `0x0800BCD8`:
Evidence `ev_706fa630ab6e08ac66461749aa8ac6ceb101ae95004f58ea522368b1d31cd235`,
from the recovery ELF with SHA-256
`3ad2cf305acb090aef48d1b21055d4a0d2862daa8262946f3eed124b47537bcf`.
This static dossier corroborates function/caller structure; it does not observe execution.

### Remaining acceptance boundary

The tested synchronous executions have matching live RAM, applicable return/register
contracts, and ordered device-boundary effects after these fixes. They do not
establish unconditional whole-firmware equivalence.

- Some machine accesses still differ: config halfword writes become byte writes,
  normal frame header stores are reordered, and channel packed-state reads occur
  at different points. No conflict was found in inspected IRQ paths, but dynamic
  DMA/UART callbacks prevent claiming every interrupt interleaving was proved.
- Stack use differs. For example, the sampled storage-read paths use at most
  64/136 bytes (original/native), write paths 96/168, and frame-send paths 16/52.
  These figures cover executed test paths, including selected driver prefixes;
  they exclude unexecuted driver bodies, nested IRQ frames and full-system peaks.
- Timing, real peripheral responses, startup/upgrade operation and IRQ/DMA
  concurrency require board evidence. No board was connected or flashed.
- Exceptional large-register transfer tests use bounded scripted failures rather
  than successful transfers through every possible 32-bit address. Zero-address
  TX tests model SRAM/Flash bytes at zero, not the hardware remapping peripheral.

Before declaring the development image an unconditional replacement, establish
board acceptance for these remaining conditions. Finite matching tests must not be
reported as an all-input/all-schedule proof.
