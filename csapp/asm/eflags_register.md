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
