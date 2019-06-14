# 汇编中的数据访问方法

处理器有多种访问数据的方式, 也就是寻址模式.

1. `immediate mode` 立即模式. 如果数据包含在指令中,比如给某一个寄存器赋一个字面量. 此时不需要给计算机提供一个值为 0 的地址,而是直接把 0 给它.
2. `register addressing mode` 寄存器寻址模式. 指令中要访问的是寄存器,而不是一个内存地址.
3. `direct addressing mode`. 直接寻址模式. 指令中包含了要访问的内存地址.
4. `indexed addressing mode`. 索引寻址模式. 指令中包含了要访问的内存地址,同时指定了一个偏移量.(也可以给偏移量指定乘数)
5. `indirect addressing mode`. 间接寻址模式. 指令中包含了一个寄存器,寄存器中包含了要访问的数据的指针.
6. `base pointer addressing mode`. 基地址寻址模式. 这种寻址模式类似于索引寻址模式. 但是偏移量寻址前是加在寄存器中的.