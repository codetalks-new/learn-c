# eflags 寄存器

eflags 的 64 位版本是 rflags 不过由于 rflags 的高 32 位保留未用.所以跟 eflags 没有你干啥来

eflags 包含了一组状态标志,一个控制标志,及一组系统标志.

| 位索引 | 分类     | 简称 | 说明                                 |
| ------ | -------- | ---- | ------------------------------------ |
| 0      | 状态标志 | CF   | Carry Flag (进位标志)                |
| 2      | 状态标志 | PF   | Parity Flag (奇偶标志)               |
| 4      | 状态标志 | AF   | Auxillary Carry Flag (辅助进位标志)  |
| 6      | 状态标志 | ZF   | Zero Flag (零标志)                   |
| 7      | 状态标志 | SF   | Sign Flag (符号标志)                 |
| 8      | 系统标志 | TF   | Trap Flag (陷入标志)                 |
| 9      | 系统标志 | IF   | Interrupt Enable Flag (中断启用标志) |
| 10     | 控制标志 | DF   | Direction Flag (方向标志)            |
| 11     | 状态标志 | OF   | Overflow Flag (溢出标志)             |
| 12-13  | 系统标志 | IOPL | I/O Privilege Level (IO 特权级别)    |
| 14     | 系统标志 | NT   | Nested Task (嵌套任务)               |
| 16     | 系统标志 | RF   | Resume Flag(恢复标志)                |
| 17     | 系统标志 | VM   | Virtual-8086 Mode(虚拟 8086 模式)    |
| 18     | 系统标志 | AC   | Alignment Check/ Access Control      |
| 19     | 系统标志 | VIF  | Virtual Interrupt Flag               |
| 20     | 系统标志 | VIP  | Virtual Interrupt Pending            |
| 21     | 系统标志 | ID   | ID Flag                              |

## 状态标志

- `CF` Carry Flag,算术运算产生了进位或者借位则设置,否则清除. 对于无符号运算来说此标志意味着溢出.
- `PF` Parity Flag, 结果的最低位字节的 1 个数为偶数则设置,否则清除.
- `AF` Axuiliary Carry Flag, 用于 BCD 计算中有超过 3 比特的结果.否则清除.
- `ZF` Zero Flag,结果为 0 则设置,否则清除.
- `SF` Sign Flag,将结果设置为最高有效位,也就是有符号数的符号位,0 表示正数,1 表示负数.
- `OF` Overflow Flag, 此标志用于有符号数(2 的补码)的溢出标志. 正数太大,负数太小时设置,否则清除.

上面这些标志中,只有 CF 可以直接被修改.

1. 通过 `STC`,`CLC`,`CMC` 指令修改.
2. 通过 `BT`,`BTS`,`BTR`和 `BTC` 复制特定的位进 `CF` 标志位.

状态标志,支持为三种不同的数据类型的单个算术运算产生结果.

1. 无符号数, `CF` 标志有进位或借位.
2. 有符号数(2 的补码), `OF` 标志有进位或借位.
3. BCD 数, `AF` 标志有进位或借位.

`ZF` 标志无符号数或者有符号数为 0.

说明:

1. `leaq` 指令不改变任何状态标志,因为它是用来进行地址计算的.
2. 对于逻辑操作, `CF`,`OF` 标志会设置为 0.
3. 对于移位操作,`CF` 将会被设置成最后一个被移出的位,`OF` 会设置为 0.
4. `INC`和 `DEC` 会设置`OF` 和 `ZF` 标志.但是不会改变进位标志.

## DF 标志

`DF` direction flag, 用来控制字符串指令 (MOVS, CMPS,SCAS,LODS,STOS).
`DF` 指令设置之后,将使字符串指令自动减(处理字符串从高地址到低地址).清除此标志将使字符串操作指令自动增(从低地址到高地址)
`STD` 指令设置此标志, `CLD` 清除此标志.

## 系统标志及 IOPL 字段

系统标志及 IOPL 字段用于控制操作系统及执行操作.
**注意**: 这些标志不应该被应用程序修改.
以下是这些系统标志的功能说明:

- `TF` Trap flag 设置后启动单步调试模式,清除则禁用.
- `IF` Interrupt enable flag, 设置此标志将禁用中断(seti),清除后启用中断.(cli)
- `NF` Nested task flag, 如果当前的任务与之前执行的任务有关联系统设置,否则清除.
- `RF` Resume flag, 控制处理器响应调试异常.
- `VM` Virtual-8086 mode flag, 设置时启用 virtual-8086 模式,清除后返回不带虚拟 8086 语义的保护模式.

## 比较和测试指令

| 指令       | 基于    | 描述 |
| ---------- | ------- | ---- |
| CMP S1,S2  | S2 - S1 | 比较 |
| TEST S1,S2 | S2 & S1 | 测试 |

1. `CMP` 指令根据两个数之差来设置状态标志位. 除了不更新目的寄存器,它跟 SUB 指令的表现一样.
2. `TEST` 指令除了不更新目的寄存器的值与 `AND` 指令一样. `test` 的典型用法是两个操作数都一样比如(test %rax,%rax 用来检查%rax 是负数,零,还是正数)

## 访问条件码

### 根据条件码设置目的寄存器值为 0 或 1

| 指令    | 同义名 | 效果             | 设置条件             |
| ------- | ------ | ---------------- | -------------------- |
| sete D  | setz   | D ⟵ ZF           | 相等/零              |
| setne D | setnz  | D ⟵ ~ZF          | 不等/非零            |
| sets D  |        | D ⟵ ZF           | 负数                 |
| setns D |        | D ⟵ ~ZF          | 非负数               |
| setl D  | setnge | D ⟵ SF^OF        | 小于(有符号<)        |
| setle D | setng  | D ⟵ (SF^OF)\|ZF  | 小于等于(有符号<=)   |
| setg D  | setnle | D ⟵ ~(SF^OF)&~ZF | 大于(有符号>)        |
| setge D | setnl  | D ⟵ ~(SF^OF)     | 大于等于(有符号>=)   |
| seta D  | setnbe | D ⟵ ~CF&~ZF      | 超过(无符号>)        |
| setae D | setnb  | D ⟵ ~CF          | 超过或相等(无符号>=) |
| setb D  | setnae | D ⟵ CF           | 低于(无符号<)        |
| setbe D | setna  | D ⟵ CF\|ZF       | 低于或等于(无符号<=) |

## 跳转指令

正常情况下,指令从上到下一条接一条执行.跳转(jump)指令会导致执行切换到一个全新的位置.
在汇编代码中,这些跳转通常用一个标号(label) 指明.

1. 直接跳转 `jmp <Label>`
2. 间接跳转,跳转地址从寄存器或者内存位置中读取的.

间接跳转的两种写法:

1. `jmp *%rax` 用寄存器 `%rax` 的值作为跳转地址.
2. `jmp *(%rax)` 以 `%rax` 作为读地址,从内存中读出跳转地址.

| 指令          | 同义名 | 跳转条件     | 描述                 |
| ------------- | ------ | ------------ | -------------------- |
| jmp Label     |        | 1            | 直接跳转             |
| jmp \*Operand |        | 1            | 间接跳转             |
| je Label      | jz     | ZF           | 相等/零              |
| jne Label     | jnz    | ~ZF          | 不相等/非零          |
| js Label      |        | SF           | 负数                 |
| jns Label     |        | ~SF          | 非负数               |
| jl Label      | jnge   | SF^OF        | 小于(有符号<)        |
| jle Label     | jng    | (SF^OF)\|ZF  | 小于或等于(有符号<=) |
| jg Label      | jnle   | ~(SF^OF)&~ZF | 大于(有符号>)        |
| jge Label     | jnl    | ~(SF^OF)     | 大于或等于(有符号>=) |
| ja Label      | jnbe   | ~CF&~ZF      | 超过(无符号>)        |
| jae Label     | jnb    | ~CF          | 超过或相等(无符号>=) |
| jb Label      | jnae   | CF           | 低于(无符号<)        |
| jbe Label     | jna    | CF\|ZF       | 低于或等于(无符号<=) |

## 跳转指令的编码

1. 在汇编中,跳转目标用符号书写.
2. 经过汇编器及后面的链接器处理之后,会产生跳转目标的适当编码.

跳转指令的编码方式

1. PC 相对编码-最常用
   PC 相对编码的方式是将目标地址指令的地址与紧跟在跳转指令后面的那条指令的地址之间的差作为编码. 这些地址你偏移量可以编码为 1,2 或 4 字节.
2. 绝对地址编码
   用 4 个字节直接指定目标

## 用条件传送指令来实现条件分支

实现条件操作的传统方法是通过使用控制的条件转移.
另一各策略是使用数据的条件转移.

以下示例是简单的表示条件控制的转移 C 代码.

```c
long absdiff(long x, long y){
  long result;
  if(x < y ){
    result = y - x;
  }else{
    result = x - y;
  }
  return result;
}
```

另一个示例是使用条件传送风格的写法.

```c
long cmovdiff(long x,long y){
  long rval = y - x;
  long eval = x - y;
  long ntest = x >= y;
  if(ntest)rval = eval; // 此行可使用一条指令来实现
  return rval;
}
```

有意思的是 `absdiff` 风格 C 语言的代码通过优化编译出来的汇编的风格,跟 `cmovdiff` 的风格却是对应的.

```
▶ cc -o absdiff.o -O1 -c csapp/asm/absdiff.c

~/Workspace/learn-c  master ✗                                                0h20m ⚑ ◒
▶ objdump -d absdiff.o

absdiff.o:      file format Mach-O 64-bit x86-64

Disassembly of section __TEXT,__text:
_absdiff:
       0:       55      pushq   %rbp
       1:       48 89 e5        movq    %rsp, %rbp
       4:       48 89 f0        movq    %rsi, %rax
       7:       48 29 f8        subq    %rdi, %rax
       a:       48 29 f7        subq    %rsi, %rdi
       d:       48 0f 4c f8     cmovlq  %rax, %rdi
      11:       48 89 f8        movq    %rdi, %rax
      14:       5d      popq    %rbp
      15:       c3      retq

```

条件传送指令,当条件满足时指令把源值 S 复制到目的 R.

| 指令       | 同义名  | 跳转条件     | 描述                 |
| ---------- | ------- | ------------ | -------------------- |
| cmove S,R  | cmovz   | ZF           | 相等/零              |
| cmovne S,R | cmovnz  | ~ZF          | 不相等/非零          |
| cmovs S,R  |         | SF           | 负数                 |
| cmovns S,R |         | ~SF          | 非负数               |
| cmovl S,R  | cmovnge | SF^OF        | 小于(有符号<)        |
| cmovle S,R | cmovng  | (SF^OF)\|ZF  | 小于或等于(有符号<=) |
| cmovg S,R  | cmovnle | ~(SF^OF)&~ZF | 大于(有符号>)        |
| cmovge S,R | cmovnl  | ~(SF^OF)     | 大于或等于(有符号>=) |
| cmova S,R  | cmovnbe | ~CF&~ZF      | 超过(无符号>)        |
| cmovae S,R | cmovnb  | ~CF          | 超过或相等(无符号>=) |
| cmovb S,R  | cmovnae | CF           | 低于(无符号<)        |
| cmovbe S,R | cmovna  | CF\|ZF       | 低于或等于(无符号<=) |

一般来说,只有在两个分支条件计算都比较简单时,才会使用条件传送指令来优化.否则分支预测错误也会导致较大的开销.
