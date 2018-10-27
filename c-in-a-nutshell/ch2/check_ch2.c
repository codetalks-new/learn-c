#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main(int argc, char const *argv[]) {
  assert(sizeof(int) >= 4);
  assert(sizeof(1) >= 4);
  assert(sizeof(short) >= 2);
  assert(sizeof(long long) >= 8);
  printf("输出类型信息\n");
  printf("默认的 char 类型：%s\n",CHAR_MIN < 0 ? "signed":"unsigned");
  printf("%10s\t%10s\t%4s\t%20s\t%20s\n","类型","字节数","位数","最小值","最大值");
  printf("%10s\t%10zu\t%4d\t%20d\t%20d\n","char",sizeof(char),CHAR_BIT, CHAR_MIN,CHAR_MAX);
  printf("%10s\t%10zu\t%4d\t%20d\t%20d\n","short",sizeof(short),0, SHRT_MIN,SHRT_MAX);
  printf("%10s\t%10zu\t%4d\t%20d\t%20d\n","int",sizeof(int),0, INT_MIN,INT_MAX);
  printf("%10s\t%10zu\t%4d\t%20ld\t%20ld\n","long",sizeof(long),LONG_BIT, LONG_MIN,LONG_MAX);
  printf("%10s\t%10zu\t%4d\t%20lld\t%20lld\n","long long",sizeof(long long),0, LLONG_MIN,LLONG_MAX);
  return 0;
}
