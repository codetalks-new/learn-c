#include <stdbool.h>
#define NEW_INT_STACK(name, size, ...)               \
  int name##_stack[size] = {__VA_ARGS__};            \
  int name##_stack_max_size = size;                  \
  int name##_stack_size = 0;                         \
  bool name##_push(int num) {                        \
    if (name##_stack_size > name##_stack_max_size) { \
      return -1;                                     \
    }                                                \
    name##_stack[++name##_stack_size] = num;         \
  }                                                  \
  int name##_pop() {                                 \
    return name##_stack[--name##_stack_size];        \
  }                                                  \
  int name##_top() {                                 \
    return name##_stack[name##_stack_size];          \
  }

#define SWAP(a, b) \
  {                \
    int tmp = a;   \
    b = a;         \
    a = tmp;       \
  }