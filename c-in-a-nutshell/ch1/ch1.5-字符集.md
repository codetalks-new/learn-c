- `translation environment` 代码编译时的环境，源代码字符集 (source character set)
- `execution environment` 程序执行时环境，运行字符集 (execution character set)

编译器会将源代码中的字符常量和字符串字面量转换成运行字符集中对应的元素。

为了验证中文编译后的存放方式。观看如下代码编译后的结果

```c
 const char *text = "aabbccdd中文";
```

反编译对应目标文件之后，可以看到其二进制表示为
`61 61 62 62 63 63 64 64 E4 B8 AD E6 96 87 00`
最后面的 `00` 表示 `\0` 字符串结束字符。因为`中文`两字的编码是 `E4 B8 AD E6 96 87`
基本判断是属于 UTF-8 的编码。
使用 `clang -S` 仅汇编发现其字符串表示为

```s
L_.str:                                 ## @.str
	.asciz	"aabbccdd\344\270\255\346\226\207"
```

此时 `strlen` 的调用是返回 `14` 也就是字符的 ascii 表示的长度。而不是，按道理其实其中只有 10 个字符。上面的编码方式是 8 进制。

## 宽字符与多字节字符

以 支持 Unicode 的编码字符集为例。

- 宽字符 UTF-16 和 UTF-32
- 多字节字符 UTF-8

当采用 Unicode 标准时。 `wchat_t` 至少是 16 位或者 32 位，其值代表一个 Unicode 字符 。
`wchat_t` 在 `stddef.h` 头文件中有定义。`wchar.h` 头包含了大部分的 `wchat_t` 类型字符，字符串的处理函数。`wchat_t` 字符串前面需要加 `L` 前缀。

C11 的新增前缀。

- `u8` 示例： `u8"中文或者其他"` 表示编码方式是 UTF-8 ，如果 C 语言的编译环境对多字节的字符的默认编码方式为 UTF-8 那 `u8` 前缀可以不加。
- `u` 前缀表示 `char16_t` 的宽字符的静态数组。
- `U` 前缀表示 `char32_t` 的宽字符的静态数组。

在 Mac 上测试如下代码时，发现中文无法输出。

```c
  const wchar_t *wtext2 = L"aabbccdd中文";
  wprintf(L"%ls wcslen -> %lu\n", wtext2, wcslen(wtext2));
```

上面宽字符对应的汇编数据如下：

```s
l_.str:
	.long	97                      ## 0x61
	.long	97                      ## 0x61
	.long	98                      ## 0x62
	.long	98                      ## 0x62
	.long	99                      ## 0x63
	.long	99                      ## 0x63
	.long	100                     ## 0x64
	.long	100                     ## 0x64
	.long	20013                   ## 0x4e2d
	.long	25991                   ## 0x6587
	.long	0                       ## 0x0
```

由于 `clang` 找不到 `<uchar.h>` 相关功能便不再分析。
