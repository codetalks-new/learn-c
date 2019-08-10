# 函数运行时栈

运行参数 `run hello world`

偏移量:是指相对于对应函数栈帧而言.

| 偏移量 | 地址  | 内容           | 备注            |
| ------ | ----- | -------------- | --------------- |
| +40    | 0x300 | 0x7ffeefbff57b | world           |
| +40    | 0x2f8 | 0x7ffeefbff575 | hello           |
| +32    | 0x2f0 | 0x7ffeefbff548 | bin/fun_stack   |
| +24    | 0x2e8 | 0x3            | argc            |
| +16    | 0x2e0 | 0x000000000000 |
| +8     | 0x2d8 | 0x7fff681783d5 |
| 0      | 0x2d0 | 0x2e0          | main 函数基地址 |
| -8     | 0x2c8 | 0x3            | argc 的副本     |
| -16    | 0x2c0 | 0x7ffeefbff2f0 | argv 的副本     |
| -24    | 0x2b8 | 0x4            | length          |
| -32    | 0x2b0 | 0x5            | width           |
| -40    | 0x2a8 | 0x100000fa3    | call 的下指令   |
| -48    | 0x2a0 | 0x2d0          | main rbp        |
| 0      | 0x2a0 |
| +8     | 0x298 | 4              | length          |
| +16    | 0x290 | 5              | length          |
| +24    | 0x288 | 0x14           | area_size       |
| +32    | 0x280 | 0x6            | unit_price      |
| +40    | 0x278 | 0x78           | price           |
| +48    | 0x270 | 0x0            |                 |

| +8 | 0x268 | 0x100000f3d |
| 0 | 0x260 | 0x2a0 |
