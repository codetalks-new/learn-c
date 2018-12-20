#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * 数字的二进制之旅 1 从一个与自己不相等的数谈起
 * by 代码会说话
 */

bool eq_self(double num) {
  return num == num ? true : false;
}
double f1 = 1.11;
double f2 = NAN;  // Not a Number 1/0
int main() {
  assert(eq_self(f1) == true);
  assert(eq_self(f2) == false);
  uint64_t f1b;
  memcpy(&f1b, &f1, sizeof f1);
  printf("%f %" PRIx64 "\n", f1, f1b);
  uint64_t f2b;
  memcpy(&f2b, &f2, sizeof f2);
  printf("%f 0x%llx\n", f2, f2b);
  return 0;
}
// nan 7ff8000000000000

// 0x7fc00000
// 0111 1111 1 100 (0000 *5)
// 1 + 8 + 1 + 22
// IEEE 754
