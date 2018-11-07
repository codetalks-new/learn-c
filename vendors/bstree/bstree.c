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

/**
 * 这里一个值得注意的点是指向指针的指针的使用。
 * 1) 在C语言中 结构体是值对象，也就是传参数的时候会传一个副本。
 * 2）为了修改结构体如 Node 的左右子节点。必须传指针。
 * 3) 在 BST 中如果要修改 bst->root 字段需要怎么传值呢？可以传 bst 指针。然后修改 bst-root 的值。
 * 4）但是上述只限于修改根节点。如果是其他分支节点假充分支为 Node *branch。这样就不行。
 * 5) branch 是一个指向 Node 的指针。`branch` 变量保存的是所指向的 Node 结构的地址值。
 * 6）
 *
 */
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
 * root->left -> []
 */
static bool insert_v2(BSTree *bst, Node *parent, const void *data, size_t size) {
  assert(parent != NULL);
  const void *lhs = bst->key(data);
  const void *rhs = bst->key(parent->data);
  if (bst->cmp(lhs, rhs) < 0) {
    if (parent->left == NULL) {
      parent->left = make_node(data, size);
      return true;
    } else {
      return insert_v2(bst, (parent->left), data, size);
    }
  } else {
    if (parent->right == NULL) {
      parent->right = make_node(data, size);
      return true;
    } else {
      return insert_v2(bst, (parent->right), data, size);
    }
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
  // v1
  // return insert(bst, &(bst->root), data, size);
  // v2
  if (bst->root == NULL) {
    bst->root = make_node(data, size);
    return true;
  } else {
    return insert_v2(bst, bst->root, data, size);
  }
}
