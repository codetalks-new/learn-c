# stack notes

## 调试准备

```
fun`main:
    0x100000f80 <+0>:  pushq  %rbp
    0x100000f81 <+1>:  movq   %rsp, %rbp
    0x100000f84 <+4>:  subq   $0x20, %rsp
    0x100000f88 <+8>:  movl   $0x0, -0x4(%rbp)
    0x100000f8f <+15>: movq   $0x3, -0x10(%rbp)
    0x100000f97 <+23>: movq   $0x4, -0x18(%rbp)
    0x100000f9f <+31>: movq   -0x10(%rbp), %rdi
    0x100000fa3 <+35>: movq   -0x18(%rbp), %rsi
->  0x100000fa7 <+39>: callq  0x100000f30 ; calc_price
    0x100000fac <+44>: movl   %eax, %ecx
    0x100000fae <+46>: movl   %ecx, %eax
    0x100000fb0 <+48>: addq   $0x20, %rsp
    0x100000fb4 <+52>: popq   %rbp
    0x100000fb5 <+53>: retq   
```
> di -p 
> re r rip rbp rsp rdi rsi rdx rcx r8 r9 rax 

## 栈值表
运行参数  `run hello world`

| rbp   | 偏移量 | 地址  | 内容        | 备注           |
| ----- | ------ | ----- | ----------- | -------------- |
|       |        | 0xee4 | USER=       | 环境变量       |
|       |        | ...   |             |                |
|       |        | 0x57d | world       | 命令行参数     |
|       |        | 0x577 | hello       | 命令行参数     |
|       |        | 0x550 | ../bin/fun  | 程序路径       |
| 0x2e0 | 32     | 0x300 | 0x550       | char *argv[]   |
| 0x2e0 | 24     | 0x2f8 | 0x003       | int argc       |
| 0x2e0 | 16     | 0x2f0 | 0x000       | int argc       |
| 0x2e0 | 8      | 0x2e8 | 0x681783d5  | int argc       |
|       |        |       | main 函数栈 |
| 0x2e0 | 0      | 0x2e0 | 0x2f0       |                |
| 0x2e0 | -8     | 0x2d8 | 0x003036    |                |
| 0x2e0 | -16    | 0x2d0 | 0x003       |                |
| 0x2e0 | -24    | 0x2c8 | 0x004       |                |
| 0x2e0 | -32    | 0x2c0 | 0x000       |                |
|       |        |       | calc_price  |                |
| 0x2b0 | 8      | 0x2b8 | 0x100000fac | call下一条指令 |
| 0x2b0 | 0      | 0x2b0 | 0x2e0       | 调用者rbp      |
| 0x2b0 | -8     | 0x2a8 | 0x003       |                |
| 0x2b0 | -16    | 0x2a0 | 0x004       |                |
| 0x2b0 | -24    | 0x298 | 0x000       |                |
| 0x2b0 | -32    | 0x290 | 0x2e8       |                |
| 0x2b0 | -40    | 0x288 | 0x300       |                |
| 0x2b0 | -48    | 0x280 | 0x000       |                |
|       |        |       | calc_area   |                |
| 0x270 | 8      | 0x278 | 0xf4d       | call下一条指令 |
| 0x270 | 0      | 0x270 | 0x2b0       | 调用者rbp      |
| 0x270 | -8     | 0x268 | 0x003       |                |
| 0x270 | -16    | 0x260 | 0x004       |                |

