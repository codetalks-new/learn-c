# Linux C 程序的解剖及汇编与反汇编
    file,readelf,objdump,as,ld 使用


## 引子
    1. 介绍两个简单实用小程序 `true` 和 `false`
    2. 查看大小,自定义实现 yes 程序,查看大小.
## 解剖 Linux C 程序.
    解剖工具
    1. `file`
    2. `xxd`
    3. `ELF` 文件基本介绍
    4. `readelf`
    5. `objdump`
 
## 如何精简Linux C 小程序
    1. stdlibc 介绍 (gnulibc)
    2. 如何去掉链接stdlibc,找不到 `_start` 的问题解决方式. 没有退出处理的问题.
    3. 提一下系统调用(保护模式,用户模式,内核模式)
    4. `strip` 介绍

## 极简小程序实现方式,纯汇编
    1. 使用 gcc 编译
    2. 使用 `as` 汇编,使用 `ld` 链接 .

    
