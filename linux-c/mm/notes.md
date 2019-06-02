
# 程序的内存布局探索

# Linux C 进程内存布局探索(1) 程内存布局基础与栈及 ASLR

参考: Linux C 程序的解剖及汇编与反汇编

## 前情提要

1. 使用 `readelf` 分析 Linux C 程序的 ELF 格式.
2. 使用 objdump 查看反汇编信息
3. as ld 极简可执行文件的实现.

## 基础

1. 64 位系统 48 位虚地址空间. (用户空间和内核空间分布及大小)
2. 查看进程的内存布局信息. `/proc/<pid>/maps` 和 `pmap -X pid`
   - 小技巧: 使用 `getchar()` 或 `while(1){sleep(100000);}` 来阻止进程马上退出 .

## 各数据类型在进程中内存的布局分布.

- 已初始化全局变量
- 未初始化全局变量
- 自定义函数
- 库函数

## 栈的增长特性

- 向下增长,随机性.
- ASLR 介绍 Address Space Layout Randomization
- 关闭随机性
  临时关闭: (`sysctl -w kernel.randomize_va_space [0,1,2] `) 或 `echo [0,1,2] > /proc/sys/kernel/randomize_va_space`
  针对指定程序关闭 `setarch`uname-m`-R program [args ...]` `-R` 的长选项是`--addr-no-randomize`
  `永久改变: 修改`/etc/sysctl.conf` 配置文件.
  其中:
  - 0 - 关闭地址空间随机化. 对应内核启动参数 `noremaps`
  - 1 启用 stack 地址, VDSO(virtual dynamic shared object)页,共享内存区域的随机化.
  - 2 增加(.data)数据段的随机化
- 也有可能受 gcc 编译影响:
  `gcc -fno-stack-protector -z execstack -o program program.c`
- ASLR 依赖于可执行文件是 PIE (Position Independent Executables)


1. readelf -l 查看程序加载进内存的段 LOAd
2. pmap <pid>
3. cat /proc/<pid>/maps

## 64
48 位 = 2*128TB
47 47

4 级 页 表 -> 64
7 级 

# 32 位 4G
[128TB ]  0xfffffffffffffff
16 * 1024 TB
[128TB ] 0 




[内核区] 128TB 

[ 16M TB 巨大空洞]

[
    128TB 用户区
[绿色通道] 7ff 
[stack] 7fffc8
[ 动态链接]  7f4ee5a15
[heap 堆]  555c51512
[ 可读写数据段]
[ 只读数据段]
[ 代码段 ]  555cc506

]



[栈]


[堆]


