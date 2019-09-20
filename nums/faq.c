#include <float.h>  // FLT_EPSILON
#include <inttypes.h>
#include <math.h>  // fabs
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// flt_epsilon

void dump_float(float *num) {
  uint32_t bits;
  memcpy(&bits, num, sizeof(float));
  printf("%f %x\n", *num, bits);
}

void recommand() {
  printf("IEEE 754 标准\n");
  printf("深入理解计算机系统(第三版) 第二章\n");
  printf("编码:隐匿在计算机软硬件背后的语言\n");
}

void float_format() {
  float total = 100;
  float failed = 29;
  float failed_percent = failed / total;
  printf("总人数:%.0f,不及格:%.0f, 不及格率: %.5f\n", total, failed,
         failed_percent);
}

void float_limit_case1() {
  /**
   * ± 1.797,693,134,862,315,7 · 10**308
   * −9,223,372,036,854,775,808 to 9,223,372,036,854,775,807, from −(2**63) to
   *(2**63-1) 1 2**53 -1 -> 9007199254740991
   * double
    snowflake
   * uint64
   * Android Java Uint64 Long Int64
   * JavaScript
   *  IEEE 754
   */

  double uid = atof("639997199254748000");
  printf("用户 ID = %.0lf\n", uid);

  // JS 中只有浮点数 double (64位)
  // Java 中没有 UInt32, UInt64
}

bool feq(float a, float b) {
  return fabs(a - b) < FLT_EPSILON;
}

void float_precision_case2() {
  float a = 0.5;
  float b = 0.25;
  float c = a + b;
  if (c == 0.75) {
    printf("Why? (0.5 + 0.25) == 0.75\n");
  } else {
    printf("That won't happen!\n");
  }
}

void float_precision_case1() {
  // CGFloat
  double a = 0.1;
  double b = 0.2;
  double c = a + b;
  printf("c=%f\n", c);
  if (feq(c, 0.3)) {
    printf("CodeTalks 保证不会进入到此分支\n");
  } else {
    printf("Why? (0.1 + 0.2) 不等于 0.3 \n");
  }
}

int main(int argc, char const *argv[]) {
  printf("欢迎来到 代码会说话 的编程实验室\n");
  printf("浮点数解惑与避坑指南(1)浮点数的坑哪些你掉过?\n");
  float_precision_case1();
  return 0;
}
