# 数据传送指令

### 简单的传送指令 MOV
| 指令        | 效果 | 描述           |
| ----------- | ---- | -------------- |
| MOV S,D     | D<-S | 传送           |
| movb        |      | 传送字节       |
| movw        |      | 传送字         |
| movl        |      | 传送双字       |
| movq        |      | 传送四字       |
| movabsq I,R | R<-I | 传送绝对的四字 |

1. 源操作数,可以是立即数,寄存器或内存地址.
2. 目的操作数,要么是寄存器要么是内存地址.
3. 64位环境下,两个操作数不能都是内存地址.
4. 对于 movl 来说,寄存器的高4字节会被置为0.

### 带符号扩展的传送指令 MOVS (Move and sign extend)
MOVS 类指令,加上源和目的操作数的后缀,有如下几种.
`movsbw`,`movsbl`,`movsbq`, `movswl`,`movswq`,`movslq`
也就是将源值较小的数复制到较大目的时的剩余字节的填充方式.
还有一个 `cltq` 表示 `convert long to quad` 指定将 %eax 寄存器中的值带符号扩展到 `%rax`
相当于 `movslq %eax, %rax` 但是编码更紧凑.

### 以零扩展的传送指令 MOVZ (Move and zero extend)
MOVZ 指令有如下搭配.
`movzbw`,`movzbl`,`movzbq`,`movwl`,`movzw`.
注意没有 `movzlq` 指令.因为 `movl` 就有这样的效果了.

  

### 简单数字传送实例解析
`-1` 的16进制表示是 `FF..F`

| 操作                              | 结果                    |
| --------------------------------- | ----------------------- |
| movabsq $0x0011223344556677, %rax | $rax = 0011223344556677 |
| movb $-1, %al                     | $rax = 00112233445566FF |
| movw $-1, %ax                     | $rax = 001122334455FFFF |
| movl $-1, %eax                    | $rax = 00000000FFFFFFFF |
| movq $-1, %rax                    | $rax = FFFFFFFFFFFFFFFF |


### 带扩展的数字传送实例解析
| 操作                             | 结果                    |
| -------------------------------- | ----------------------- |
| movabsq $0x0011223344556677 %rax | $rax = 0011223344556677 |
| movb $0xAA, %dl                  | $dl = AA                |
| movb %dl,%al                     | $rax = 00112233445566AA |
| movsbq %dl,%rax                  | $rax = FFFFFFFFFFFFFFAA |
| movzbq %dl,%rax                  | $rax = 00000000000000AA |
