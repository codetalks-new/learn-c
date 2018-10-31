#include <assert.h>
#include "../../vendors/stest/stest.h"
#include <stdio.h>

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

static void test_structs(){
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
}


union Word
{
  int16_t word;
  struct { int8_t low,high;}; //因为一般是小端序，所以低字节在前
};

union Doubleword{
  int32_t double_word;
  struct{
    union Word low;
    union Word high;
  };
};


static void test_anonymous_union_struct(){
  union Word word = { 126 };
  assert(word.high == 0);
  assert(word.low == 126);
  printf("sizeof union Word %lu,sizeof word:%lu\n",sizeof(union Word), sizeof(word));
  assert(sizeof(word) == 2);
  union Doubleword dw = { 1024 };
  assert(dw.low.word == 1024);
  assert(dw.high.word == 0);
  assert(sizeof(dw) == 4);
}  

int main(int argc, char const *argv[]) {
  test_structs();
  test_anonymous_union_struct();
  return 0;
}
