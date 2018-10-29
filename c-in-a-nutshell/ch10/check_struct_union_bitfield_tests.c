#include <assert.h>
#include "../../vendors/stest/stest.h"

struct _Song{
  char title[64];
  int bit_rate;
};
typedef struct _Song Song;
typedef struct{
  char name[20];
  /**
   * 'm' 表示男，'f' 表示女，
   */
  char gender; 
} Singer;

/// 前置声明及空声明与声明屏蔽
struct Foo;
struct Bar{struct Foo *pFoo;};
struct Foo{struct Bar *pBar;};

int main(int argc, char const *argv[]) {
  Song s1 = {.title = "简单爱", 128*1000};
  assert_str_eq(s1.title, "简单爱");
  Song s2 = s1;
  strcpy(s2.title, "晴天");
  // s2.title = "晴天";
  // expression must be a modifiable lvalue
  assert_str_eq(s1.title, "简单爱");
  assert_str_eq(s2.title, "晴天");

  Singer chou = {.name = "周杰伦",.gender = 'm'};
  assert_str_eq(chou.name, "周杰伦");
  assert(chou.gender == 'm');
  assert(sizeof(chou) >= 21);
  assert(sizeof(Singer) >= 21);
  assert(__offsetof(Singer, gender) >= 20);
  // test 布局逻辑
  assert_str_eq((const char * )&chou, "周杰伦");
  const Singer * chou2 = (const Singer *)&chou.name;
  assert(chou2->gender == 'm');
  assert((*chou2).gender == 'm');
  return 0;
}
