# 1 "pre_c.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 361 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "pre_c.c" 2
# 21 "pre_c.c"
void debug(const char *msg) {
  const char *tip = "我们于开发环境";
}
# 40 "pre_c.c"
# 1 "./pre_common.h" 1
# 1 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/10.0.0/include/stdbool.h" 1 3 4
# 2 "./pre_common.h" 2
# 41 "pre_c.c" 2
# 1 "./pre_module1.h" 1
# 1 "./pre_common.h" 1
# 1 "./pre_module1.h" 2
# 42 "pre_c.c" 2
int nums_stack[100] = {1, 3, 4};
int nums_stack_max_size = 100;
int nums_stack_size = 0;
_Bool nums_push(int num) {
  if (nums_stack_size > nums_stack_max_size) {
    return -1;
  }
  nums_stack[++nums_stack_size] = num;
}
int nums_pop() {
  return nums_stack[--nums_stack_size];
}
int nums_top() {
  return nums_stack[nums_stack_size];
}
int bits_stack[100] = {};
int bits_stack_max_size = 100;
int bits_stack_size = 0;
_Bool bits_push(int num) {
  if (bits_stack_size > bits_stack_max_size) {
    return -1;
  }
  bits_stack[++bits_stack_size] = num;
}
int bits_pop() {
  return bits_stack[--bits_stack_size];
}
int bits_top() {
  return bits_stack[bits_stack_size];
}

int main() {
  nums_push(3);
  nums_push(4);
  int n4 = nums_pop();
  int a = 3;
  int b = 4;
  if (a > b) do {
      (a)++;
      (b)++;
    } while (0);
  else
    b++;
  int tmp = 8;
  {
    int tmp = a;
    b = a;
    a = tmp;
  };
  int c = ((1 + 1) * (1 + 1));
  return (((++a) > (b)) ? (++a) : (b));
}
