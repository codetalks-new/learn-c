[Linux 编程实践] 基本 I/O 模型,描述符,管道及重定向, stdin,stdout,stderr

- by 代码会说话

了解基本的 I/O 模型,描述符,管道,对于 Linux 下的文件编程及 bash 下的命令编写或者理解都大有帮助.

### 先看一个小实例

1. 有一个简单的 C 语言小程序

```
▶ ./redirect
输出到标准输出
输出到标准错误输出
```

2. 可以使用 SHELL 的 重定向功能将输出重定向到一个文件.如:
   执行过程如下:

```
▶ ./redirect > output.txt
输出到标准错误输出
```

3. 如上,有部分内容没有被重定向. `output.txt` 中的内容只有一行.使用 `cat` 命令查看如下:

```
▶ cat output.txt
输出到标准输出
```

### 文件描述符

| 索引(编号) | 已打开文件信息结构体  | 文件流 |
| ---------- | --------------------- | ------ |
| 0          | /dev/ttys001 输入设备 | stdin  |
| 1          | /dev/ttys002 输出设备 | stdout |
| 2          | /dev/ttys003 错误设备 | stderr |

| 1 | app.log | stdout |
| 2 | app.log | stdout |

| 1 | /dev/ttys002 输出设备 | stdout |
| 2 | /dev/ttys002 输出设备 | stderr |
| 1 | app.log | stdout |

继续阅读本文前可以先看一下以下几个问题?

1. 一些命令中常见的 `&> /dev/null` 是什么意思?

2. `>` 和 `>>` 的差别.

3. `2 > err.log` 是有什么用? `2>&1` 又是什么意思?

4. 库函数 `fread`,`fwrite` 与 `read` 和 `write` 系统调用的对比.

## 当我们打开一个文件时,我们打开了什么?

不同的文件一般都会使用专用的程序打开. 打开的结果千差万别.

但是从编程的脚本来看,他们都相关无几,如果从系统内核的观点来看更是相同.

下面我们都将以普通的文本文件为例进行简单的说明.

### C 语言级别的简单文件读写.

`FILE *` 指针是不透明的(也就是具体实现不可见)

打开文件 `FILE *fopen( const char *restrict filename, const char *restrict mode );`

读文件 `size_t fread( void *restrict buffer, size_t size, size_t count, FILE *restrict stream );`

写文件 `size_t fwrite( const void *restrict buffer, size_t size, size_t count, FILE *restrict stream );`

### 系统级别的简单文件读写

`FILENO` 整数,是进程已经打开的文件表的索引.

注意基本系统调用添加头文件声明 `<unistd.h>`,文件打开需要头文件 `<fctnl.h>`

打开文件 `int open(const char *pathname, int flags, mode_t mode);`

读文件 `ssize_t read(int fildes, void *buf, size_t nbyte);`

写文件 ​`ssize_t write(int fildes, const void *buf, size_t nbyte);`
