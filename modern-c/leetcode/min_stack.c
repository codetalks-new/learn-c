/**
 *
 LeetCode 155. 最小栈 数据结构设计题 C语言实现
 by 代码会说话
 设计一个支持 push，pop，top 操作，
 并能在常数时间内检索到最小元素的栈。

push(x) -- 将元素 x 推入栈中。
pop() -- 删除栈顶的元素。
top() -- 获取栈顶元素。
getMin() -- 检索栈中的最小元素。
示例:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
 */
#include <assert.h>
#include <stdlib.h>

typedef struct Element {
  int num;
  int currentMin;
} Element;

typedef struct MinStack {
  int size;
  Element* elements;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
  MinStack* st = malloc(sizeof(MinStack));
  st->size = 0;
  st->elements = calloc(maxSize, sizeof(Element));
  return st;
}

int minStackTop(MinStack* obj) {
  Element* top = &(obj->elements[obj->size - 1]);
  return top->num;
}

void minStackPush(MinStack* obj, int x) {
  int currentMin = x;
  if (obj->size > 0) {
    Element* e = &(obj->elements[obj->size - 1]);
    if (e->currentMin < currentMin) {
      currentMin = e->currentMin;
    }
  }
  Element* cur = &(obj->elements[obj->size]);
  cur->num = x;
  cur->currentMin = currentMin;
  obj->size++;
}

void minStackPop(MinStack* obj) {
  obj->size--;
}

int minStackGetMin(MinStack* obj) {
  Element* top = &(obj->elements[obj->size - 1]);
  return top->currentMin;
}

void minStackFree(MinStack* obj) {
  free(obj->elements);
  free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */
int main() {
  struct MinStack* obj = minStackCreate(20);
  minStackPush(obj, -2);
  minStackPush(obj, 0);
  minStackPush(obj, -3);
  assert(minStackGetMin(obj) == -3);
  minStackPop(obj);
  assert(minStackTop(obj) == 0);
  assert(minStackGetMin(obj) == -2);

  return 0;
}
