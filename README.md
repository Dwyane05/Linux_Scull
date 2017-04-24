# Linux 设备驱动程序模块抽取分析

### 前言

  学习内核相关的东西完整算起来一年半了，不得不说内核的学习是一个学习成本很高的东西，慢慢摸索也逐渐的有了感悟，简单来说，需要如下的几个阶段：

1.基础阶段   （操作系统，C、asm 编程语言，LINUX系统编程）

2.中级阶段   （了解内核架构，API，学习编写内核模块)

3.中高级阶段 （开发独立功能点，驱动程序的学习与编写）

4.高级阶段   （参与内核的开发）


我现在将《Linux设备驱动程序（第3版）》简称LDD3 中内容整理，抽取。由于这本书的内核版本有点老。我就把代码都移植到了我4.0.4的内核上，调通运行，既是自己的
学习也是为了后续同学们学习内核提供点参考资料。考研不易，已是见缝插针，难免有错误疏漏之处还请指正。

### 章节

*[基础设备驱动程序](./simple_basic/README.md)


*[内核测试/PROC创建文件](./test_kernel/README.md)


*[竞态与并发与内核锁机制](./concur/README.md)


*[高级IO与阻塞](./higher_scull/README.md)


*[时间与延时](./timer_s/README.md)


*[分配内存](./alloc_mem/README.md)


*[IO端口通信](./IO_port/README.md)


*[内核数据类型](./kernel_DS/README.md)


*[内核中断处理](./interrupt/README.md)


*[PCI驱动程序](./PCI_driver/README.md)




