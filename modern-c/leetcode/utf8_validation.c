
/**
 *
 亲自写代码验证字节数组是否符合UTF-8编码规范 LeetCode 393 by 代码会说话

 UTF-8 中的一个字符可能的长度为 1 到 4 字节，遵循以下的规则：

对于 1 字节的字符，字节的第一位设为0，后面7位为这个符号的unicode码。
对于 n 字节的字符 (n > 1)，第一个字节的前 n 位都设为1，第 n+1
位设为0，后面字节的前两位一律设为10。剩下的没有提及的二进制位，全部为这个符号的unicode码。
这是 UTF-8 编码的工作方式：



给定一个表示数据的整数数组，返回它是否为有效的 utf-8 编码。

注意:
输入是整数数组。只有每个整数的最低 8
个有效位用来存储数据。这意味着每个整数只表示 1 字节的数据。

示例 1:

data = [197, 130, 1], 表示 8 位的序列: 11000101 10000010 00000001.

返回 true 。
这是有效的 utf-8 编码，为一个2字节字符，跟着一个1字节字符。
示例 2:

data = [235, 140, 4], 表示 8 位的序列: 11101011 10001100 00000100.

返回 false 。
前 3 位都是 1 ，第 4 位为 0 表示它是一个3字节字符。
下一个字节是开头为 10 的延续字节，这是正确的。
但第二个延续字节不以 10 开头，所以是不符合规则的。
 *
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/**
 *
+---------------------------------------------
| 0xxxxxxx
| 110xxxxx 10xxxxxx
| 111xxxx 10xxxxxx 10xxxxxx
| 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx


0000
8421
0000 -> 0x00 ->
1100 -> 0xc
1110 -> 0xe
1111 -> 0xf

1000 0000 0x80 & byte == 0
0xxx xxxx

1110 0000 0xe0 & byte == 0xc0
1100 0000
1100 0000

1111  0xf0 & byte == 0xe0

11111 0xf8 & byte == 0xf0

0xc0 & byte == 1000 0000 = 0x80
9->9
10 -> a
11 -> b
12 -> c
13 -> d
14 -> e
15 -> f
 */

int calcBytes(const int byte) {
  if ((byte & 0x80) == 0) {
    return 1;
  } else if ((byte & 0xe0) == 0xc0) {
    return 2;
  } else if ((byte & 0xf0) == 0xe0) {
    return 3;
  } else if ((byte & 0xf8) == 0xf0) {
    return 4;
  } else {
    return -1;
  }
}

bool validUtf8(const int* data, int dataSize) {
  for (int i = 0; i < dataSize;) {
    int bytes = calcBytes(data[i]);
    if (bytes < 1) {
      return false;
    }
    // 1
    // i = 0 bytes 2
    if ((i + bytes) > dataSize) {
      return false;
    }
    for (int j = i + 1; j < i + bytes; j++) {
      if ((data[j] & 0xc0) == 0x80) {
        continue;
      } else {
        return false;
      }
    }
    i += bytes;
  }
  return true;
}

int main() {
  const char* greeting = "你好,世界!Hello World!";
  const wchar_t* wgreeting = L"你好,世界!Hello World!";
  // printf("%s\n", greeting);
  const int data1[] = {197, 130, 1};
  assert(validUtf8(data1, 3) == true);
  const int data2[] = {235, 140, 4};
  assert(validUtf8(data2, 3) == false);
  return 0;
}