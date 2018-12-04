/**
 * @代码会说话 codetalks
 */
#include <stdio.h>

typedef struct Point2D {
  int x, y;
} Point2D;

typedef struct Point3D {
  struct Point2D;
  int z;
} Point3D;

void print_point2d(Point2D *p) { printf("Point2D(%d, %d)\n", p->x, p->y); }
void print_point3d(Point3D *p) { printf("Point3D(%d, %d, %d)\n", p->x, p->y, p->z); }

int main(int argc, char const *argv[]) {
  Point2D p1 = {.x = 3, .y = 4};
  print_point2d(&p1);
  Point3D p2 = {.x = 3, .y = 4, .z = 5};
  print_point3d(&p2);
  return 0;
}

// clang -fms-extensions inlined_struct.c && ./a.out
