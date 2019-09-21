#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 1:  0001
 2:  0010

 3:  0011
 4:  0100

 5:  0101
 6:  0110

 7:  0111
 8:  1000

 N&(N-1)

 9:  1001
 10: 1010

假设有一个数 N:
1. N 是奇数, 那么 N -1 是偶数. 那么 N 的二进制位比 N-1 多且仅只多最后一位.
 N & (N-1) -> 消掉最后一位
2. N 是偶数, 那么 N-1 是奇数, 那么...

 N&(N-1) -> 相与之后 N 的二进制表示的最后一位被消掉了.
*/

/*
编写一个函数，输入是一个整数，返回其二进制表达式中数字位数为 ‘1’ 的个数
*/
int count_of_1(int16_t num) {
  int cnt = 0;
  while (num != 0) {
    num = num & (num - 1);
    cnt += 1;
  }
  return cnt;
}
void demo2_count_of_1() {
  printf("%d 二进制表示中1的个数:%d\n", 0x0, count_of_1(0x0));
  printf("%d 二进制表示中1的个数:%d\n", 0x1, count_of_1(0x1));
  printf("%d 二进制表示中1的个数:%d\n", 0x2, count_of_1(0x2));
  printf("%d 二进制表示中1的个数:%d\n", 0x3, count_of_1(0x3));
  printf("%d 二进制表示中1的个数:%d\n", 0x4, count_of_1(0x4));
  printf("%d 二进制表示中1的个数:%d\n", 0x10, count_of_1(0x10));
  printf("%d 二进制表示中1的个数:%d\n", 0x7f, count_of_1(0x7f));
  // 0111 1111
  printf("%d 二进制表示中1的个数:%d\n", 0x8f, count_of_1(0x8f));
  printf("%d 二进制表示中1的个数:%d\n", 0x8fff, count_of_1(0x8fff));
}
char *bool_to_str(bool b) {
  return b ? "true" : "false";
}

// 判断是否是奇数
bool is_odd(int num) {
  // return num % 2 == 1;  // bad
  // return num % 2 != 0;  // ok
  // xxx1
  return (num & 0x1) == 0x1;  // good
}

void demo1_is_odd() {
  printf("%d 是奇数吗? %s\n", 2, bool_to_str(is_odd(2)));
  printf("%d 是奇数吗? %s\n", 3, bool_to_str(is_odd(3)));
  printf("%d 是奇数吗? %s\n", -2, bool_to_str(is_odd(-2)));
  printf("%d 是奇数吗? %s\n", -3, bool_to_str(is_odd(-3)));
}

int main(int argc, char const *argv[]) {
  // 位运算误区与技巧(1) - by 代码会说话
  // demo1_is_odd();
  demo2_count_of_1();
  return 0;
}
