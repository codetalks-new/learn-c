#include<stdio.h>
#include<assert.h>
#include<string.h>

#define typeOf1(x) _Generic((x), int:"int",double:"double")
#define typeOf2(x) _Generic((x), int:"int",double:"double",default:"nid")

int main(int argc, char const *argv[]) {
  assert(strcmp(typeOf1(1) , "int") == 0);
  assert(strcmp(typeOf1('c') , "int") == 0);
  assert(strcmp(typeOf1(1.0) , "double") == 0);
  // assert(strcmp(typeOf1("a") , "double") != 0);
  // no association matches the selector type "char [2]"
  assert(strcmp(typeOf2("a") , "nid") == 0);
  return 0;
}
