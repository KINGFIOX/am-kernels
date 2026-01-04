# benchmark

## microbench

```
wangfiox@ubuntu2504:~/Documents/ysyx-workbench/am-kernels/benchmarks/microbench$ make run
# Building microbench-run [riscv32-nemu]
+ CC src/bench.c
+ CC src/sieve/sieve.c
+ CC src/qsort/qsort.c
+ CC src/md5/md5.c
+ CC src/fib/fib.c
+ CXX src/15pz/15pz.cc
+ CXX src/ssort/ssort.cc
# Building am-archive [riscv32-nemu]
+ CC src/platform/nemu/trm.c
+ CC src/platform/nemu/ioe/timer.c
+ CC src/platform/nemu/ioe/input.c
+ CC src/platform/nemu/ioe/gpu.c
+ CC src/platform/nemu/ioe/audio.c
+ CC src/platform/nemu/ioe/disk.c
+ CC src/riscv/nemu/cte.c
+ CC src/riscv/nemu/vme.c
+ AR -> build/am-riscv32-nemu.a
# Building klib-archive [riscv32-nemu]
+ CC src/stdio.c
+ CC src/stdlib.c
+ CC src/string.c
+ CC src/cpp.c
+ AR -> build/klib-riscv32-nemu.a
# Creating image [riscv32-nemu]
+ LD -> build/microbench-riscv32-nemu.elf
+ OBJCOPY -> build/microbench-riscv32-nemu.bin
mainargs=
make -C /home/wangfiox/Documents/ysyx-workbench/nemu ISA=riscv32 run ARGS="-b -l /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/microbench/build/nemu-log.txt" IMG=/home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/microbench/build/microbench-riscv32-nemu.bin
make[1]: Entering directory '/home/wangfiox/Documents/ysyx-workbench/nemu'
make[2]: Entering directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Entering directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench'
/home/wangfiox/Documents/ysyx-workbench/nemu/build/riscv32-nemu-interpreter -b -l /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/microbench/build/nemu-log.txt  /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/microbench/build/microbench-riscv32-nemu.bin
[src/utils/log.c:30 init_log] Log is written to /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/microbench/build/nemu-log.txt
[src/memory/paddr.c:50 init_mem] physical memory area [0x80000000, 0x87ffffff]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'serial' at [0xa00003f8, 0xa00003ff]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'rtc' at [0xa0000048, 0xa000004f]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'vgactl' at [0xa0000100, 0xa0000107]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'vmem' at [0xa1000000, 0xa10752ff]
VMware: No 3D enabled (0, Success).
libEGL warning: egl: failed to create dri2 screen
MESA: error: ZINK: failed to choose pdev
libEGL warning: egl: failed to create dri2 screen
VMware: No 3D enabled (0, Success).
libEGL warning: egl: failed to create dri2 screen
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'keyboard' at [0xa0000060, 0xa0000063]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'audio' at [0xa0000200, 0xa0000217]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'audio-sbuf' at [0xa1200000, 0xa120ffff]
[src/monitor/monitor.c:60 load_img] The image is /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/microbench/build/microbench-riscv32-nemu.bin, size = 32848
[src/monitor/monitor.c:29 welcome] Trace: OFF
[src/monitor/monitor.c:33 welcome] Build time: 15:20:21, Jan  3 2026
Welcome to riscv32-NEMU!
For help, type "help"
Empty mainargs. Use "ref" by default
======= Running MicroBench [input *ref*] =======
[qsort] Quick sort: * Passed.
  min time:  ms [893]
[queen] Queen placement: * Passed.
  min time:  ms [390]
[bf] Brainf**k interpreter: * Passed.
  min time:  ms [262]
[fib] Fibonacci number: * Passed.
  min time:  ms [207]
[sieve] Eratosthenes sieve: * Passed.
  min time:  ms [284]
[15pz] A* 15-puzzle search: * Passed.
  min time:  ms [428]
[dinic] Dinic's maxflow algorithm: * Passed.
  min time:  ms [566]
[lzip] Lzip compression: * Passed.
  min time:  ms [294]
[ssort] Suffix sort: * Passed.
  min time:  ms [536]
[md5] MD5 digest: * Passed.
  min time:  ms [144]
==================================================
MicroBench PASS        400 Marks
                   vs. 100000 Marks (i9-9900K @ 3.60GHz)
Scored time:  ms
Total  time:  ms
[src/cpu/cpu-exec.c:215 cpu_exec] nemu: HIT GOOD TRAP at pc = 0x80004c44
[src/cpu/cpu-exec.c:172 statistic] host time spent = 54,968,694 us
[src/cpu/cpu-exec.c:173 statistic] total guest instructions = 1,842,524,329
[src/cpu/cpu-exec.c:175 statistic] simulation frequency = 33,519,521 inst/s
make[1]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench/nemu'
```

## dhrystone

```
wangfiox@ubuntu2504:~/Documents/ysyx-workbench/am-kernels/benchmarks/dhrystone$ make run
# Building dhrystone-run [riscv32-nemu]
+ CC dry.c
# Building am-archive [riscv32-nemu]
# Building klib-archive [riscv32-nemu]
# Creating image [riscv32-nemu]
+ LD -> build/dhrystone-riscv32-nemu.elf
+ OBJCOPY -> build/dhrystone-riscv32-nemu.bin
mainargs=
make -C /home/wangfiox/Documents/ysyx-workbench/nemu ISA=riscv32 run ARGS="-b -l /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/dhrystone/build/nemu-log.txt" IMG=/home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/dhrystone/build/dhrystone-riscv32-nemu.bin
make[1]: Entering directory '/home/wangfiox/Documents/ysyx-workbench/nemu'
make[2]: Entering directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Entering directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench'
/home/wangfiox/Documents/ysyx-workbench/nemu/build/riscv32-nemu-interpreter -b -l /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/dhrystone/build/nemu-log.txt  /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/dhrystone/build/dhrystone-riscv32-nemu.bin
[src/utils/log.c:30 init_log] Log is written to /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/dhrystone/build/nemu-log.txt
[src/memory/paddr.c:50 init_mem] physical memory area [0x80000000, 0x87ffffff]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'serial' at [0xa00003f8, 0xa00003ff]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'rtc' at [0xa0000048, 0xa000004f]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'vgactl' at [0xa0000100, 0xa0000107]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'vmem' at [0xa1000000, 0xa10752ff]
VMware: No 3D enabled (0, Success).
libEGL warning: egl: failed to create dri2 screen
MESA: error: ZINK: failed to choose pdev
libEGL warning: egl: failed to create dri2 screen
VMware: No 3D enabled (0, Success).
libEGL warning: egl: failed to create dri2 screen
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'keyboard' at [0xa0000060, 0xa0000063]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'audio' at [0xa0000200, 0xa0000217]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'audio-sbuf' at [0xa1200000, 0xa120ffff]
[src/monitor/monitor.c:60 load_img] The image is /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/dhrystone/build/dhrystone-riscv32-nemu.bin, size = 25072
[src/monitor/monitor.c:29 welcome] Trace: OFF
[src/monitor/monitor.c:33 welcome] Build time: 15:20:21, Jan  3 2026
Welcome to riscv32-NEMU!
For help, type "help"
Dhrystone Benchmark, Version C, Version 2.2
Trying 500000 runs through Dhrystone.
Finished in 6813 ms
==================================================
Dhrystone PASS         129 Marks
                   vs. 100000 Marks (i7-7700K @ 4.20GHz)
[src/cpu/cpu-exec.c:215 cpu_exec] nemu: HIT GOOD TRAP at pc = 0x800010c0
[src/cpu/cpu-exec.c:172 statistic] host time spent = 6,814,663 us
[src/cpu/cpu-exec.c:173 statistic] total guest instructions = 219,507,763
[src/cpu/cpu-exec.c:175 statistic] simulation frequency = 32,211,095 inst/s
make[1]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench/nemu'
```

## coremark

```
wangfiox@ubuntu2504:~/Documents/ysyx-workbench/am-kernels/benchmarks/coremark$ make run
# Building coremark-run [riscv32-nemu]
+ CC src/core_state.c
+ CC src/core_main.c
+ CC src/core_list_join.c
+ CC src/core_portme.c
+ CC src/core_util.c
+ CC src/core_matrix.c
# Building am-archive [riscv32-nemu]
# Building klib-archive [riscv32-nemu]
# Creating image [riscv32-nemu]
+ LD -> build/coremark-riscv32-nemu.elf
+ OBJCOPY -> build/coremark-riscv32-nemu.bin
mainargs=
make -C /home/wangfiox/Documents/ysyx-workbench/nemu ISA=riscv32 run ARGS="-b -l /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/coremark/build/nemu-log.txt" IMG=/home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/coremark/build/coremark-riscv32-nemu.bin
make[1]: Entering directory '/home/wangfiox/Documents/ysyx-workbench/nemu'
make[2]: Entering directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Entering directory '/home/wangfiox/Documents/ysyx-workbench'
make[2]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench'
/home/wangfiox/Documents/ysyx-workbench/nemu/build/riscv32-nemu-interpreter -b -l /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/coremark/build/nemu-log.txt  /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/coremark/build/coremark-riscv32-nemu.bin
[src/utils/log.c:30 init_log] Log is written to /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/coremark/build/nemu-log.txt
[src/memory/paddr.c:50 init_mem] physical memory area [0x80000000, 0x87ffffff]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'serial' at [0xa00003f8, 0xa00003ff]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'rtc' at [0xa0000048, 0xa000004f]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'vgactl' at [0xa0000100, 0xa0000107]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'vmem' at [0xa1000000, 0xa10752ff]
VMware: No 3D enabled (0, Success).
libEGL warning: egl: failed to create dri2 screen
MESA: error: ZINK: failed to choose pdev
libEGL warning: egl: failed to create dri2 screen
VMware: No 3D enabled (0, Success).
libEGL warning: egl: failed to create dri2 screen
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'keyboard' at [0xa0000060, 0xa0000063]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'audio' at [0xa0000200, 0xa0000217]
[src/device/io/mmio.c:52 add_mmio_map] Add mmio map 'audio-sbuf' at [0xa1200000, 0xa120ffff]
[src/monitor/monitor.c:60 load_img] The image is /home/wangfiox/Documents/ysyx-workbench/am-kernels/benchmarks/coremark/build/coremark-riscv32-nemu.bin, size = 21160
[src/monitor/monitor.c:29 welcome] Trace: OFF
[src/monitor/monitor.c:33 welcome] Build time: 15:20:21, Jan  3 2026
Welcome to riscv32-NEMU!
For help, type "help"
Running CoreMark for 1000 iterations
2K performance run parameters for coremark.
CoreMark Size    : 666
Total time (ms)  : 9631
Iterations       : 1000
Compiler version : GCC14.2.0
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0xd340
Finised in 9631 ms.
==================================================
CoreMark PASS       303 Marks
                vs. 100000 Marks (i7-7700K @ 4.20GHz)
[src/cpu/cpu-exec.c:215 cpu_exec] nemu: HIT GOOD TRAP at pc = 0x80002608
[src/cpu/cpu-exec.c:172 statistic] host time spent = 9,632,978 us
[src/cpu/cpu-exec.c:173 statistic] total guest instructions = 313,830,377
[src/cpu/cpu-exec.c:175 statistic] simulation frequency = 32,578,749 inst/s
make[1]: Leaving directory '/home/wangfiox/Documents/ysyx-workbench/nemu'
```
