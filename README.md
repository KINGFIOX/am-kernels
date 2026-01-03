AbstractMachine kernels

CONTACTS

Bug reports and suggestions go to Yanyan Jiang (jyy@nju.edu.cn) and Zihao 
Yu (yuzihao@ict.ac.cn).

> 我发现这个abstract-machine, 他有点类似于外核, 给上层程序提供用于操作硬件的库函数
>
> AM 是什么?
> 目标：给上层（比如 nanos-lite / 用户程序）提供一套统一 API，让同一份上层代码能在不同“硬件/平台”上跑起来。
> 形式：一堆库函数 + 少量底层启动/中断/IO 相关代码；按平台做适配（你看到的 am/src/platform/nemu/* 就是 NEMU 平台适配层）。
>
> 它跟“外核”像在哪里
> 把硬件操作变成库接口：例如把“读写设备寄存器、获取时间、输出字符、处理中断”等做成函数/接口，上层直接调用。
> 尽量薄：AM 不追求提供复杂的 OS 抽象（文件系统/进程/虚存等），这些通常由更上层的 nanos-lite 或你后续实现来做。
>
> 它跟真正外核不完全一样的点
> 外核强调“内核只做保护与复用，资源管理策略交给库 OS”，并且通常有明确的保护边界（用户态/内核态、权限控制、资源隔离）。
> 在 ysyx/AM 这里：
> AM 更偏教学用的跨平台 HAL/Runtime：让程序在 NEMU/真机/其他平台跑得通。
> 资源管理/隔离不是它的核心目标（尤其在 NEMU 环境下很多东西本来就是模拟出来的）。