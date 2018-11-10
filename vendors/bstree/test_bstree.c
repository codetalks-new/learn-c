#include "../stest/stest.h"
#include "bstree.h"
#include <assert.h>
#include <stdio.h>

static int int_cmp(int *lhs, int *rhs) {
  const int lhsValue = *lhs;
  const int rhsValue = *rhs;
  return lhsValue - rhsValue;
}

/**
 *       10
 *    /      \
 *   4      15
 *   \      / |
 *    7    14 18
 *         /
 *        11
 */
int main(int argc, char const *argv[]) {
  BSTree *bst = new_bst((CmpFn *)int_cmp, NULL);
  assert(bst != NULL);
  assert(bst->root == NULL);
  assert(bst->cmp != NULL);
  assert(bst->key != NULL);
  const int rootValue = 10;
  bool r1 = bst_insert(bst, &rootValue, sizeof(int));
  assert(r1 == true);
  assert(bst->root != NULL);
  assert(*(bst->root->data) == rootValue);
  const int l1 = 4;
  bool r2 = bst_insert(bst, &l1, sizeof(l1));
  assert(r2 == true);
  assert(bst->root->left != NULL);
  assert(*(bst->root->left->data) == l1);
  const int l2 = 7;
  bool r3 = bst_insert(bst, &l2, sizeof(l2));
  assert(r3 == true);
  assert(bst->root->left->right != NULL);
  assert(*(bst->root->left->right->data) == l2);
  bst_erase(bst, &l1);
  // detach_min(&bst->root->left); // 节点4是最小值将会被删除
  assert(bst->root->left);
  assert(*(bst->root->left->data) == 7);
  return 0;
}
