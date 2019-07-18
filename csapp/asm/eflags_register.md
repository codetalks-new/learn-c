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
- `OF` Overflow Flag, 此标志用于有符号数(2 的补码)的溢出标志.

上面这些标志中,只有 CF 可以直接被修改.

1. 通过 `STC`,`CLC`,`CMC` 指令修改.
2. 通过 `BT`,`BTS`,`BTR`和 `BTC` 复制特定的位进 `CF` 标志位.

状态标志,支持为三种不同的数据类型的单个算术运算产生结果.

1. 无符号数, `CF` 标志有进位或借位.
2. 有符号数(2 的补码), `OF` 标志有进位或借位.
3. BCD 数, `AF` 标志有进位或借位.

`ZF` 标志无符号数或者有符号数为 0.

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
