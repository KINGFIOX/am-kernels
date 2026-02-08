# SoC Tests

针对 NPC SoC 外设的测试程序集合。

## 目录结构

```
soc-tests/
├── Makefile # 主 Makefile, 参考 cpu-tests/Makefile
├── include/
│   └── trap.h
└── tests/
    ├── flash/ # Flash 读取测试
    │   ├── Makefile
    │   ├── flash-read.c
    │   └── article.txt
    ├── ...
```

## 使用方法

```bash
# 运行所有测试
make ARCH=riscv32-npc run
# 只运行 flash 目录下的测试
make ARCH=riscv32-npc ALL=flash run
# 清理
make clean
```

## 测试列表

| 测试目录 | 说明                                             |
| -------- | ------------------------------------------------ |
| `flash`  | XIP Flash 读取测试，从 0x30000000 读取内容并打印 |
