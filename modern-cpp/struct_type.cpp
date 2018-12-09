#include <cassert>

typedef struct Point {
  int x, y;
} Point;

typedef struct Vector {
  int x, y;
} Vector;

int main() {
  Point p1 = {3, 4};
  Vector* v_ptr = reinterpret_cast<Vector*>(&p1);
  Vector v1 = *v_ptr;
  assert(v1.x == p1.x);
  assert(v1.y == p1.y);
}
