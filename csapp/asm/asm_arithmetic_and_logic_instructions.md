## 二进制算术运算指令 (Binary Arithmetic Instructions)

| 指令     | 效果           | 描述                                  |
| -------- | -------------- | ------------------------------------- |
| ADD S,D  | D ⟵ D + S      | 加(add integers)                      |
| ADC S,D  | D ⟵ D + S + CF | 进位加(add integers with carry)       |
| SUB S,D  | D ⟵ D - S      | 减(subtract integers)                 |
| SBB S,D  | D ⟵ D - S - CF | 借位减(subtract integers with borrow) |
| INC D    | D ⟵ D + 1      | 加 1(increment)                       |
| DEC D    | D ⟵ D - 1      | 减 1(increment)                       |
| NEG D    | D ⟵ -D         | 取负 (negate)                         |
| MUL S,D  | D ⟵ D \* S     | 无符号相乘 (unsigned multiply)        |
| IMUL S,D | D ⟵ D \* S     | 相乘 (signed multiply)                |
| DIV S,D  | D ⟵ D \* S     | 无符号除法 (unsigned divide)          |
| IDIV S,D | D ⟵ D \* S     | 相除 (signed divide)                  |

## 逻辑运算指令 (Logical Instructions)

| 指令    | 效果       | 描述 |
| ------- | ---------- | ---- |
| AND S,D | D ⟵ D & S  | 与   |
| OR S,D  | D ⟵ D \| S | 或   |
| XOR S,D | D ⟵ D ^ S  | 异或 |
| NOT D   | D ⟵ ~D     | 取补 |

## 移位及旋转操作 (Shift and Rotate Instructions)

| 指令    | 效果                 | 描述                                |
| ------- | -------------------- | ----------------------------------- |
| SAL k,D | D ⟵ D<<k             | 左移(shift arithmetic left)         |
| SHL k,D | D ⟵ D<<k             | 左移(shift logical left) 等同于 SAL |
| SAR k,D | D ⟵ D>><sub>A</sub>k | 算术右移(shift arithmetic right)    |
| SHR k,D | D ⟵ D>><sub>L</sub>k | 逻辑右移(shift logic right)         |

注意:

1. 移位量也可以放在单字节寄存器`%cl`中.
2. 移位操作对于 N 位长的数据值进行操作时,移位量是由低 m 位决定的.其中 2\*\*m = N ,后面的高位会被忽略.

## 加载有效地址 LEA

lea(load effective address) 指令实际上是 mov 指令的变形,它的指示形式是从内存读取数据到寄存器,但是实际上它根本就没有引用内存.
它的第一个操作数看上去是一个内存引用,但是该指令并不是从指定位置读入数据,而是将有效地址写入到目的操作数. 这条指令可以为后面的内存引用产生指针.
另外,它还可以简洁地描述普通算术操作.例如: 如果寄存器 %rdx 的值为 x, 那么指令 `lea 7(%rdx, %rdx, 4),%rax`
将设置寄存器 %rax 的值为 `5x +7`

示例 C 程序:

```c
long scale(long x, long y,long z){
  long t = x + 4*y + 12*z;
  return t;
}
```

对应汇编是:

```asm
scale:
  leaq (%rdi, %rsi, 4), %rax  # x + 4*6
  leaq (%rdx, %rdx,2), %rax  # z + 2*z = 3*z
  leaq (%rax, %rdx, 4), %rax # (x+4*y) + 4 *(3*z) = x + 4*6 + 12*z
  ret
```
