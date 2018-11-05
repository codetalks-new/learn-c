#include "../stest/stest.h"
#include "bstree.h"
#include <assert.h>
#include <stdio.h>

static int int_cmp(int *lhs, int *rhs) {
  const int lhsValue = *lhs;
  const int rhsValue = *rhs;
  return lhsValue - rhsValue;
}

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
  bool r2 = bst_insert(bst, &l1, sizeof(int));
  assert(r2 == true);
  assert(bst->root->left != NULL);
  assert(*(bst->root->left->data) == l1);
  return 0;
}
