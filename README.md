# 固件源码重建

从 `stm32_fw.hex` 与 `主板.png` 恢复的代码和构建工程位于 [`recovery/`](recovery/README.md)。主板主控为 Geehy APM32F030C8T6。

```sh
make -C recovery
make -C recovery verify
```

- [完整汇编工程](recovery/full_assembly/README.md)：从源码独立构建 ELF/BIN/HEX，全部64 KiB与原固件逐字节一致。
- [完整 C 语义模型](recovery/full_c/README.md)：全部已识别指令的可编译C表达，用于电脑端分析和验证。
- [全函数 C 反编译稿](recovery/decompiled/README.md)：433个函数，保留反编译警告。
- [代码阅读地图](recovery/MODULE_MAP.md)：人工整理的启动、升级、协议、主循环、业务逻辑入口。

原生固件由汇编工程构建；C语义模型与反编译稿不等同于已经找回的原始纯C/Keil工程。原HEX未修改，没有执行烧录。
