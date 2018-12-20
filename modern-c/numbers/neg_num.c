#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * 二进制与负数 by 代码会说话
 * 1 = 01
 * 2 = 10
 * 3 = 11
 *
 * 0b 0xff
 */
int main() {
  int8_t nums[] = {0,   1,    2,    3,    4,   111, 125, 126,
                   127, -128, -127, -126, -15, -3,  -2,  -1};
  for (int i = 0; i < 14; i++) {
    const int8_t num = nums[i];
    uint8_t num2b;
    memcpy(&num2b, &num, sizeof num);
    printf("%4d 0x%x\n", num, num2b);
  }
  return 0;
}

/**
 *
 *
 111 - 126
 = 111 + (999 - 126) + 1 - 1000
 = 111 + (873) + 1 - 1000
 = 111 + 874 - 1000
 = 985 - 1000
 = -15

 111 - 126 = 111 + (-126)
 -0x6f = 0110 1111
 -0x82 = 1000 0010
       = 1111 0001
       = 0xf1
       = -15
126 = 0x7e

1111 1111
0111 1110
1000 0001 + 1

1000 0010 -126
0x82
*/