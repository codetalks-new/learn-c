# LLDB 使用简介

1. 命令通用格式: `<noun> <verb> [-options [option-value]] [argument [argument...]]`

## GDB 和 LLDB 命令对照表

### 执行命令

| GDB                     | LLDB                                | 备注                                                                          |
| ----------------------- | ----------------------------------- | ----------------------------------------------------------------------------- |
|                         |                                     | Do a source level single step in the currently selected thread                |
|                         | thread step-in                      |
| step                    | step                                |
| s                       | s                                   |
|                         |                                     | Do a source level single step over the currently selected thread              |
|                         | thread step-over                    |
| next                    | next                                |
| n                       | n                                   |
|                         |                                     | Do a instruction level single step in the currently selected thread           |
| stepi                   | thread step-inst                    |
| si                      | si                                  |
|                         |                                     | Do a instruction level single step in the currently selected thread           |
| nexti                   | thread step-inst-over               |
| ni                      | ni                                  |
|                         |                                     | Step out of the currently selected frame                                      |
|                         | thread step-out                     |
| finish                  | finish                              |
|                         |                                     | Return immediately from the currently selected frame, with an optional value. |
| return <expr>           | thread return <expr>                |
|                         |                                     | Stop hook                                                                     |
|                         | target stop-hook <cmd>              |
|                         |                                     | Launch a process                                                              |
|                         | process launch                      |
| run                     | run                                 |
| r                       | r                                   |
| run <args>              | process launch -- <args>            |
| run <args>              | run <args>                          |
| set args <args>         | settings set target.run-args <args> |
| gdb --args a.out <args> | lldb -- a.out <args>                |

2. 环境变量设置
   - GDB:
     - **set env DEBUG 1**
     - **unset env DEBUG**

- LLDB
  - **settings set target.env-vars DEBUG=1**
  - **set se target.env-vars DEBUG=1**
  - **env DEBUG=1**
  - **settings remove target.env-vars DEBUG**
  - **set rem target.env-vars DEBUG**

3. 显示当前调试程序的参数列表

- GDB: **show args**
- LLDB: **settings show target.run-args**

4. 附加到进程 ID 为 123.

- GDB: **attach 123**
- LLDB:
  - **process attach --pid 123**
  - **attach -p 123**

5. 附加到名为 `a.out` 的进程

   - GDB: **attach a.out**
   - LLDB: **process attach --name a.out** 或 **pro at -n a.out**

6. 等待名为 `a.out` 的进程启动并附加

   - GDB: **attach -waitfor a.out**
   - LLDB: **process attach --name a.out --waitfor** 或 **pro at -n a.out -w**

7. 附加到一个本地 GDB 协议服务器,端口 8000

   - GDB: **target remote localhost:8000**
   - LLDB: **gdb-remote 8000**

8. 运行到 12 行或离开此函数时停止
   - GDB: **until 12**
   - LLDB: **thread until 12**

### 断点命令

1. 设置根据函数名 `main` 设置断点

   - `GDB`
     - break main
   - `LLDB`
     - breakpoint set --name main
     - br s -n main
     - b main

2. 在文件`test.c` 的第 12 行处设置断点
   - `GDB`
     - break test.c:12
   - `LLDB`
     - breakpoint set --file test.c --line 12
     - br s -f test.c -l 12
     - b test.c:12
3. 为所有 C++方法名为`main`的方法设置断点.

   - `GDB`
     - break main (如果名为 main 的 c 函数则不行)
   - `LLDB`
     - breakpoint set --method main
     - br s -M main

4. 基于函数名使用正则表达式来设置断点

   - `GDB`
     - rbreak regular-expression
   - `LLDB`
     - breakpoint set --func-regex regular-expression
     - br s -r regular-expression

5. 设置条件断点
   - `GDB`
     - break foo if strcmp(y,"hello") == 0
   - `LLDB`
     - breakpoint set --name foo --condition '(int)strcmp(y,"hello") == 0'
     - br s -n foo -c '(int)strcmp(y,"hello")==0'
6. 列出所有断点
   - `GDB`
     - info break
   - `LLDB`
     - breakpoint list
     - br l
7. 删除一个断点
   - `GDB`
     - delete 1
   - `LLDB`
     - breakpoint delete 1
     - br del 1

### 检查变量

1. 列出当前帧的参数及局部变量

   - **GDB**: `info args` 和 `info locals`
   - **LLDB**: `frame variable` 或 `fr v`

2. 仅显示当前帧的局部变量

   - **GDB**: `info locals`
   - **LLDB**: `frame variable --no-args` 或 `fr v -a`

3. 显示局部变量`bar` 的内容

   - **GDB**: `p bar`
   - **LLDB**: `frame variable bar` 或 `fr v bar` 或 `p bar`

4. 以 16 进制显示局部变量`bar` 的内容

   - **GDB**: `p/x bar`
   - **LLDB** `frame variable --format x bar` 或 `fr v -f x bar`

5. 显示全局变量`baz` 的内容

   - **GDB**: `p baz`
   - **LLDB**: `target variable baz` 或 `ta v bar` 或 `p bar`

6. 显示定义在当前源文件的全局/静态变量.
   -- **LLDB** `target variable` 或 `ta v`

7. 每一次停止时显示 `argc` 和 `argv` 变量.
   - **GDB**
     - display argc
     - display argv
   - **LLDB**
     - target stop-hook add --one-liner "frame variable argc argv"
     - ta st a -o "fr v argc argv"
     - display argc
     - display argv

### 求值

1. 在当前帧执行一个普通语句

   - **GDB** `print (int)printf("Print Nine: %d",4+5)` 或 `call (int)printf("Print nine:%d.", 4+5)`
   - **LDB** `expr (int)printf("Print nine:%d.", 4 + 5)` 或使用 print 别名. `expr (int)printf("Print nine:%d.", 4 + 5)`

2. 创建并且一个恰当的变量赋值

   - **GDB**
     - set \$foo = 5
     - set variable \$foo = 5
     - print \$foo = 5
     - call \$foo = 5
     - set \$foo = (unsigned int) 5
   - **LLDB** 使用 `expr` 语句跟 C 语言的声明语句一致.
     - expr unsigned int \$foo = 5

3. 调用一个函数然后在函数的断点中停止

   - **GDB** 先 `set unwindonsignal 0` 再执行 `p fun_with_a_breakpoint()`
   - **LLDB** `expr -i 0 -- fun_with_a_breakpoint()`

4. 调用一个会崩溃的函数,然后在崩溃时停止

   - **GDB** 先 `set unwindonsignal 0` 然后执行 `p fun_which_crashes()`
   - **LLDB** `expr -u 0 -- fun_with_crashes()`

5. 输出一个 ObjC 对象的"description"
   - **GDB** `po [SomeClass returnAnObject]`
   - **LLDB**
     - `expr -o -- [SomeClass returnAnObject]`
     - `po [SomeClass returnAnObject]`

1) 列出程序的线程

   - **GDB** `info threads`
   - **LLDB** `thread list`

2) 选择线程 1 作为后续命令的默认线程

   - **GDB** `thread 1`
   - **LLDB** `thread select 1` 或 `t 1`

3) 显示当前线程的栈帧记录

   - **GDB** `bt`
   - **LLDB** `thread backtrace` 或 `bt`

4) 显示所有线程的栈帧记录

   - **GDB** `thread apply all bt`
   - **LLDB** `thread backtrace all` 或 `bt all`

5) 选择当前线程前 5 个栈帧

   - **GDB** `bt 5`
   - **LLDB**
     - `thread backtrace -c 5`
     - `bt 5`
     - `bt -c 5`

6) 选择当前线程对应索引的栈帧

   - **GDB** `frame 12`
   - **LLDB** `frame select 12` 或 `fr s 12` 或 `f 12`

7) 显示当前线程的当前栈帧的信息

   - **LLDB** `frame info`

8) 选择调用了当前栈帧的调用者的栈帧.

   - **GDB** `up`
   - **LLDB** `up` 或 `frame select --relative=1`

9) 选择被当前栈帧的调用的栈帧.

   - **GDB** `down`
   - **LLDB** `down` 或 `frame select --relative=-1` 或 `fr s -r-1`

10) 使用相对偏移量选择相对当前栈帧的栈帧.

    - **GDB** `up 2` ,`down 3`
    - **LLDB** `frame select --relative=2` 或 `fr s -r1`, `frame select --relative -3` 或 `fr s -r-3`

11) 显示当前线程的能用寄存器

    - **GDB** `info registers`
    - **LLDB** `register read` 或 `re r`

12) 给当前线程的寄存器 `rax` 写入一个十进制值.

    - **GDB** `p $rax=123`
    - **LLDB** `register write rax 123` 或 `re w rax 123`

13) Skip 8 bytes ahead of the current program counter (instruction pointer). Note that we use backticks to evaluate an expression and insert the scalar result in LLDB.

    - **GDB** `jump *$pc+8`
    - **LLDB** _register write pc`\$pc+8`_

14) LLDB 还支持指定格式的显示,格式字符基本与`printf` 函数相符. `register read --format i` 或 `re r -f i` 也支持 GDB 风格的格式化如 `register read/d`

15) 显示所有寄存器类型的所有寄存器值

- **GDB** `info all-registers`
- **LLDB** `register read --all` 或 `re r -a`

16. 显示名为 `rax`,`rsp`,`rbp` 寄存器的值.

    - **GDB** `info all-registers rax rsp rbp`
    - **LLDB** `register read rax rsp rbp`

17. 以二进制的格式显示 `rax` 寄存器的值.

    - **GDB** `p/t $rax`
    - **LLDB** `register read --format binary rax` 或 `re r -f b rax` 或 `re r/t rax` 或 `p/t $rax`

18. 从内存地址 0xbffff3c0 起读取 4 个 uint32_t 的 16 进制格式的值

    - **GDB** `x/4xw 0xbffff3c0`
    - **LLDB**
      - `memeory read --size 4 --format x --count 4 0xbffff3c0`
      - `me r -s4 -fx -c4 0xbffff3c0`
      - `x -s4 -fx -c4 0xbffff3c0`
      - `memeory read/4xw 0xbffff3c0`
      - `x/4xw 0xbffff3c0`
      - `memeory read --gdb--format 4xw 0xbffff3c0`

19. 读取表达式开始的内存 `argv[0]`

    - **GDB** `x argv[0]`
    - **LLDB** `memory read \`argv[0]\``

20. 从指定位置读取 512 字节内存数据然后以文件形式写入到一个本地.

    - **GDB** gdb 操作需要以下 4 步.
      1. `set logging on`
      2. `set logging file /tmp/mem.txt`
      3. `x/512bx 0xbffff3c0`
      4. `set logging off`
    - **LLDB**
      - `memory read --outfile /tmp/mem.txt --count 512 0xbffff3c0`
      - `me r -o/tmp/mem.txt -c512 0xbffff3c0`
      - `x/512bx -o/tmp/mem.txt 0xbffff3c0`

21. 保存指定范围的内存的二进制数据到一个文件.

    - **GDB** `dump memory /tmp/mem.bin 0x1000 0x2000`
    - **LLDB**
      - `memory read --outfile /tmp/mem.bin --binary 0x1000 0x2000`
      - `me r -o /tmp/mem.bin -b 0x10000 0x20000`

22. 反编译当前帧的当前函数.

    1.  **GDB** `disassemble`
    2.  **LLDB** `dissamble --frame` 或 `di -f`

23. 反编译名称为 main 的函数.

    1.  **GDB** `disassemble main`
    2.  **LLDB** `disassemble --name main` 或 `di -n main`

24. 反编译指定地址范围

    1. **GDB** `disassemble 0x1eb8 0x1ec3`
    2. **LLDB**
       1. `disassemble --start-address 0x1eb8 --end-address 0x1ec3`
       2. `di -s 0x1eb8 -e 0x1ec3`

25. 反编译指定位置开始的 20 条指令.
    1.  **GDB** `x/20i 0x1eb8`
    2.  **LLDB**
        1.  `disassemble --start-address 0x1eb8 --count 20`
        2.  `di -s 0x1eb8 -c 20`

LLDB 的 disassemble 更多特性.

1. 混合显示当前栈的当前函数的汇代码和反汇编. `disassemble --frame --mixed` 或 `di -f -m`
2. 显示指令编码 `--bytes` 或 `-b`
3. 仅反编译当前源代码行 `--line` 或 `-l`
4. 仅反编译当前 pc 上下的指令 `--pc` 或 `-p`

### 可执行文件及共享库查询命令

1. 列出主可执行文件及其依赖的所有共享库.

   - **GDB** `info shared`
   - **LLDB** `image list`

2. 查找可执行文件及共享库指定地址的相关信息.

   1. **GDB** `info symbol 0x1ec4`
   2. **LLDB** `image lookup --address 0x1ecd4` 或 `im loo -a 0x1ec4`

3. 查询满足指定指定正则表达式的函数

   1. **GDB** `info function <FUNC_REGEX>`
   2. **LLDB**
      1. `image lookup -r -n <FUNC_REGEX>` 查找调试符号
      2. `image lookup -r -s <FUNC_REGEX>` 查找非调试符号

4. 查找类型名为 `Point` 的信息

   1. **GDB** `ptype Point`
   2. **LLDB** `image lookup --type Point` 或 `im loo -t Point`

### 其他

1. 搜索某一个关键词相关命令的帮助

   - **GDB** `apropos keyword`
   - **LLDB** `apropos keyword`

2. 输出一些文件到当前屏幕
   - **GDB** `echo Here is some text\n`
   - **LLDB** `script print "Here is some text"
