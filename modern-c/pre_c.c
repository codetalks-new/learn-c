/**
 * 一种观点：当我们学 C语言时，我们其实在学两种语言。
 * 一种是预编译语言，另一种是 C语言。
 * by 代码会说话
 * 1. 条件编译 系统预定义 echo "" | clang -dM -E -xc - > clang_pre.h
 * 2. 宏
 *    1. 替换
 *    2. 连接 ##
 *    3. 技巧
 *      1） 括号 2)副作用 3)大括号与作用域 do while(0) 与分号
 * 3. 包含
 * 4. 抛出错误
 * 5. 实现定义
 * 6. 文件名和行信息
 *
 * 模板， -> html
 *
 */

#define DEV 1
void debug(const char *msg) {
#if DEBUG
  const char *tip = "我们于调试环境";
#elif DEV
  const char *tip = "我们于开发环境";
#else
  const char *tip = "我们于生产环境";
#endif
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define SQRT(a) ((a) * (a))

#define INC_ALL(a, b) \
  do {                \
    (a)++;            \
    (b)++;            \
  } while (0)

#include "pre_common.h"
#include "pre_module1.h"
NEW_INT_STACK(nums, 100, 1, 3, 4)
NEW_INT_STACK(bits, 100)

int main() {
  nums_push(3);
  nums_push(4);
  int n4 = nums_pop();
  int a = 3;
  int b = 4;
  if (a > b)
    INC_ALL(a, b);
  else
    b++;
  int tmp = 8;
  SWAP(a, b);
  int c = SQRT(1 + 1);
  return MAX(++a, b);
}
