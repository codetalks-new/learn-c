
#include <assert.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* makeNode(int val) {
  ListNode* node = malloc(sizeof(ListNode));
  node->val = val;
  node->next = NULL;
  return node;
}

typedef struct IntArray {
  int* data;
  int size;
} IntArray;

ListNode* arrayToList(IntArray iarr) {
  const int size = iarr.size;
  const int* array = iarr.data;
  if (size < 1) {
    return NULL;
  }
  ListNode* head = makeNode(array[0]);
  ListNode* p = head;
  for (int i = 1; i < size; i++) {
    p->next = makeNode(array[i]);
    p = p->next;
  }
  return head;
}

IntArray listToArray(ListNode* head) {
  IntArray iarr = {NULL, 0};
  int cur_max_size = 16;
  iarr.data = malloc(cur_max_size * sizeof(int));  // 预先分配一个空间的内存
  ListNode* p = head;
  int size = 0;
  while (p) {
    iarr.data[size] = p->val;
    size += 1;
    if (size >= cur_max_size) {
      cur_max_size += 16;
      iarr.data = realloc(iarr.data, sizeof(int) * cur_max_size);
    }
    p = p->next;
  }
  iarr.size = size;
  return iarr;
}

void assertArrayEqual(IntArray iarr1, IntArray iarr2) {
  assert(iarr1.size == iarr2.size);
  const int size = iarr1.size;
  for (int i = 0; i < size; i++) {
    assert(iarr1.data[i] == iarr2.data[i]);
  }
}
