# 汇编中的数据访问方法

处理器有多种访问数据的方式, 也就是寻址模式.

1. `immediate mode` 立即模式. 如果数据包含在指令中,比如给某一个寄存器赋一个字面量. 此时不需要给计算机提供一个值为 0 的地址,而是直接把 0 给它.
2. `register addressing mode` 寄存器寻址模式. 指令中要访问的是寄存器,而不是一个内存地址.
3. `direct addressing mode`. 直接寻址模式. 指令中包含了要访问的内存地址.
4. `indexed addressing mode`. 索引寻址模式. 指令中包含了要访问的内存地址,同时指定了一个偏移量.(也可以给偏移量指定乘数)
5. `indirect addressing mode`. 间接寻址模式. 指令中包含了一个寄存器,寄存器中包含了要访问的数据的指针.
6. `base pointer addressing mode`. 基地址寻址模式. 这种寻址模式类似于索引寻址模式. 但是偏移量寻址前是加在寄存器中的.

##  汇编语言中的寻址模式表示法
`address_or_offset(%base_or_offset, %index, multiplier)`
最终的地址计算算法如下:
`final_address = address_or_offset + %base_or_offset + multiplier * %index

说明:
  1. `address_or_offset` 和 `multiplier` 只能是常量.
  2. `%base_or_offset` 和 `%index` 必须是寄存器.
  3. 上述4个字段都是可选的.
  4. multiplier 必须 是 1,2,4或者8.

1. 直接寻址(direct addressing mode)
  `mov address, %eax `  address 使用的就是上面寻址模式中的 `address_or_offset` 部分. 此指令表示将 `address` 内存地址处的值加载进 `%eax` 寄存器处.

2. 索引寻址模式(indexed addressing mode)
  `mov str_start(,%ecx, 1), %eax` 此指令的内存地址由上面公式中的 `address_or_offset` 和 `%index` 现部分一直计算得到. %index 对应的寄存器可以使用其他能用寄存器. 此指令是为了寻找字符串的对应索引的内存地址,所以 `multiplier` 设置为1,因为 `char` 类型长度为1. 如果是访问双字节,和字可以将其`multiplier` 指定为 `2` 或 `4`

3. 间接寻址模式(indirect addressing mode)
 `mov (%eax), %ebx` 指令表示, `%eax` 寄存上保存某内存地址, 将此内存地址的值加载进 `%ebx` 寄存器中.

4. 基址寻址模式
  `mov 4(%eax), %ebx` ,类似于上面的间接寻址模式,但是还需要加上一个常量.

5. 立即寻址模式(immediate mode)
  这其实不需要寻找,操作数直接是数值或其他字面量.
  `mov $12,%eax` 将 十进制值为12的数值加载进 %eax 寄存器.

