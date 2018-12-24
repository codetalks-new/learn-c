#include "common/ListNode.h"

// typedef struct ListNode ListNode;
ListNode* reverseListR(ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  ListNode* newHead = reverseListR(head->next);
  head->next = NULL;
  ListNode* p = newHead;
  while (p->next) {
    p = p->next;
  }
  p->next = head;
  return newHead;
}

ListNode* reverseList(ListNode* head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }
  int max_size = 16;
  ListNode** larr = malloc(16 * sizeof(ListNode*));
  int size = 0;
  ListNode* p = head;
  // 模拟栈
  while (p) {
    larr[size] = p;
    size += 1;
    if (size >= max_size) {
      max_size += 16;
      larr = realloc(larr, sizeof(ListNode*) * max_size);
    }
    p = p->next;
  }
  // 模拟出栈
  int i = size - 1;
  ListNode* newHead = larr[i];
  p = newHead;
  while (--i > -1) {
    p->next = larr[i];
    p = p->next;
    p->next = NULL;
  }
  return newHead;
}

// Line 70: Char 15: runtime error: member access within misaligned address
// 0x000000002011 for type 'struct ListNode', which requires 8 byte alignment
// (ListNode.c)

int main() {
  int arr1[] = {1, 2, 3, 4, 5};
  IntArray iarr = {NULL, 5};
  iarr.data = arr1;

  int arr2[] = {5, 4, 3, 2, 1};
  IntArray iarr2 = {NULL, 5};
  iarr2.data = arr2;

  ListNode* l1 = arrayToList(iarr);
  ListNode* l2 = reverseList(l1);
  IntArray iarrAct = listToArray(l2);
  assertArrayEqual(iarrAct, iarr2);
}