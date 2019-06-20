/**
 *
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序
的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
 */
#include <stdbool.h>
#include <stdlib.h>
#include "common/ListNode.h"

// typedef struct ListNode ListNode;
typedef void* AnyPtr;

typedef struct PtrStack {
  AnyPtr* ptrs;
  int size;
  int capacity;
} PtrStack;

bool ptr_stack_is_empty(PtrStack* st) {
  return st->size == 0;
}
static const int STACK_STEP_SIZE = 64;
PtrStack* ptr_stack_create() {
  PtrStack* st = malloc(sizeof(PtrStack));
  st->capacity = STACK_STEP_SIZE;
  st->size = 0;
  st->ptrs = malloc(sizeof(void*) * st->size);
  return st;
}

void ptr_stack_push(PtrStack* st, void* data) {
  st->ptrs[st->size] = data;
  st->size += 1;
}

void* ptr_stack_pop(PtrStack* st) {
  if (st->size < 1) {
    return NULL;
  }
  assert(st->size > 0);
  st->size -= 1;
  return st->ptrs[st->size];
}

PtrStack* listToStack(ListNode* head) {
  PtrStack* st = ptr_stack_create();
  ListNode* p = head;
  while (p) {
    ptr_stack_push(st, p);
    p = p->next;
  }
  return st;
}

ListNode* reverseList(ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }
  PtrStack* st = listToStack(head);
  ListNode* newHead = ptr_stack_pop(st);
  ListNode* p = newHead;
  p->next = NULL;
  while (!ptr_stack_is_empty(st)) {
    p->next = ptr_stack_pop(st);
    p = p->next;
    p->next = NULL;
  }
  return newHead;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  if (l1 == NULL) {
    return l2;
  }
  if (l2 == NULL) {
    return l1;
  }
  PtrStack* st1 = listToStack(l1);
  PtrStack* st2 = listToStack(l2);
  ListNode* next = NULL;
  int carry = 0;
  while (!ptr_stack_is_empty(st1) || !ptr_stack_is_empty(st2)) {
    ListNode* node1 = ptr_stack_pop(st1);
    ListNode* node2 = ptr_stack_pop(st2);
    int val1 = node1 ? node1->val : 0;
    int val2 = node2 ? node2->val : 0;

    int sum = val1 + val2 + carry;
    int val = sum % 10;
    carry = sum / 10;
    ListNode* sumNode = malloc(sizeof(ListNode));
    sumNode->val = val;
    sumNode->next = next;
    next = sumNode;
  }
  if (carry > 0) {
    ListNode* sumNode = malloc(sizeof(ListNode));
    sumNode->val = carry;
    sumNode->next = next;
    next = sumNode;
  }
  return reverseList(next);
}

int main() {
  int arr1[] = {2, 4, 3};
  IntArray ia1 = {NULL, 3};
  ia1.data = arr1;

  int arr2[] = {5, 6, 4};
  IntArray ia2 = {NULL, 3};
  ia2.data = arr2;

  ListNode* l1 = arrayToList(ia1);
  ListNode* l2 = arrayToList(ia2);
  ListNode* l3 = addTwoNumbers(l1, l2);

  IntArray act = listToArray(l3);
  int expectArr[] = {7, 0, 8};
  IntArray ia3 = {NULL, 3};
  ia3.data = expectArr;
  assertArrayEqual(act, ia3);
}