#include <assert.h>
#include "../../vendors/stest/stest.h"
#include <stdio.h>

// float *func()[3][10];
// function returning array is not allowed
float (*func ())[3][10];

// extern char * *fTab[](void);
// array of functions is not allowed
 extern char * (*fTab[])(void);

 extern const volatile int ticks;


int main(int argc, char const *argv[]) {
  char *abc[10];
  char (*bcd)[10];
  static_assert(sizeof(abc) == 80, "abc 数组大小应该是10个指针大小");
  static_assert(sizeof(bcd) == 8, "bcd 应该是一个指针大小");
  printf("sizeof abc %lu", sizeof(abc));
  printf("sizeof bcd %lu", sizeof(bcd));
  return 0;
}
