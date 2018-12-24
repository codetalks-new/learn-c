/**
 *
将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "common/ListNode.h"

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
  if (l1 == NULL) {
    return l2;
  }
  if (l2 == NULL) {
    return l1;
  }
  ListNode* p1 = l1;
  ListNode* p2 = l2;
  ListNode* head = NULL;
  ListNode* p = NULL;
  ListNode* cur = NULL;
  while (p1 && p2) {
    if (p1->val < p2->val) {
      cur = p1;
      p1 = p1->next;
    } else {
      cur = p2;
      p2 = p2->next;
    }
    if (head) {
      p->next = cur;
      p = cur;
    } else {
      head = cur;
      p = head;
    }
  }
  p->next = p1 ? p1 : p2;

  return head;
}

int main() {
  int arr1[] = {1, 2, 4};
  int arr2[] = {1, 3, 4};
  IntArray iarr1 = {NULL, 3};
  IntArray iarr2 = {NULL, 3};
  iarr1.data = arr1;
  iarr2.data = arr2;

  int expArray1[] = {1, 1, 2, 3, 4, 4};
  IntArray expIarr = {NULL, 6};
  expIarr.data = expArray1;

  ListNode* l1 = arrayToList(iarr1);
  ListNode* l2 = arrayToList(iarr2);
  ListNode* l3 = mergeTwoLists(l1, l2);

  IntArray actIarr = listToArray(l3);
  assertArrayEqual(expIarr, actIarr);
  return 0;
}
