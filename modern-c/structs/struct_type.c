/**
 * @代码会说话
 * C 结构按的类型匹配的问题及内存布局兼容性问题。
 * 后续会有一些利用内存布局兼容性扩展视频
 */
#include <assert.h>

typedef struct Point {
  int x, y;
} Point;

typedef struct Vector {
  int x, y;
} Vector;

int main() {
  Point p1 = {3, 4};
  Vector v1 = *(Vector *)(&p1);
  assert(v1.x == p1.x);
  assert(v1.y == p1.y);

  Point p2 = p1;
  p2.x = 2;
  assert(p1.x == 3);

  v1.x = 1;
  assert(p1.x == 3);
}
