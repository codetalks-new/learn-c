#include "bstree.h"

/**
 * 默认的 BSTree key 提取函数。
 */
BSTREE_API const void *defaultKey(const void *data) { return data; }

/**
 * 创建空的 BSTree
 *
 * @param cmp  两个数据项比较函数 nonnull
 * @param key key 提取函数 nullable, 如果为 null 使用 defaultKey 函数。
 * @see defaultKey()
 * @return 返回创建的 BSTree
 */
BSTREE_API BSTree *new_bst(CmpFn *cmp, KeyFn *key) {
  BSTree *tree = malloc(sizeof(BSTree));
  tree->cmp = cmp;
  tree->key = (key != NULL) ? key : defaultKey;
  tree->root = NULL;
  return tree;
}

static Node *make_node(const void *data, size_t size) {
  const size_t node_size = sizeof(Node) + size;
  Node *node = malloc(node_size);
  node->left = NULL;
  node->right = NULL;
  node->size = size;
  memcpy(node->data, data, size);
  return node;
}

static bool insert(BSTree *bst, Node **ppNode, const void *data, size_t size) {
  Node *parent = *ppNode;
  if (parent == NULL) {
    parent = make_node(data, size);
    *ppNode = parent;
    return true;
  }
  const void *lhs = bst->key(data);
  const void *rhs = bst->key(parent->data);
  if (bst->cmp(lhs, rhs) < 0) {
    return insert(bst, &(parent->left), data, size);
  } else {
    return insert(bst, &(parent->right), data, size);
  }
}

/**
 * 向 BST 中插入节点。
 *
 * @param bst BST
 * @param data 要插入的节点的数据
 * @param size 要插入节点的数据的大小。
 * @return 插入成功返回 true,否则返回 false
 */
BSTREE_API bool bst_insert(BSTree *bst, const void *data, size_t size) {
  if (bst == NULL || data == NULL || size == 0) {
    return false;
  }
  return insert(bst, &(bst->root), data, size);
}
