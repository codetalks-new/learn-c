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
 * 6）要修改 branch 指针的值而不是其指向的值。则需要取 branch 值的地址。
 * 7）如果将branch 作为值传递
 * 而不是其指针的话，因为指针值存储的是整型，所以最终会得到传递的是一个branch所保存的值的一个副本，这样便无法对此值进行取地址了。
 * 9) 如果将branch作为指针传递，当 branch 为 NULL时，无法取其地址。
 * 10）所以传 branch 的指针，这样便不会为 NULL了。
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

static const void *search(BSTree *bst, const Node *parent, const void *key) {
  if (parent == NULL) {
    return NULL;
  }
  const int cmp_res = bst->cmp(key, bst->key(parent->data));
  if (cmp_res == 0) {
    return parent->data;
  } else if (cmp_res < 0) {
    return search(bst, parent->left, key);
  } else {
    return search(bst, parent->right, key);
  }
}

/**
 * 从 BST 中搜索指定的 key
 * @param bst BSTree
 * @param key 要搜索的节点数据的  key
 * @return 如果搜索得到返回对应的数据，搜索不到返回NULL。
 *
 */
BSTREE_API const void *bst_search(BSTree *bst, const void *key) {
  if (bst == NULL || key == NULL) {
    return NULL;
  }
  return search(bst, bst->root, key);
}

static void clear(Node *parent) {
  if (parent == NULL) {
    return;
  }
  clear(parent->left);
  clear(parent->right);
  free(parent);
}

/**
 * 删除 BST 的所有节点
 * @param bst BSTree
 */
BSTREE_API void bst_clear(BSTree *bst) {
  if (bst == NULL) {
    return;
  }
  clear(bst->root);
  bst->root = NULL;
}

/**
 * 查找并删除子树的最小节点
 *
 * 1. 如果有左子树，递归调用左子树即可。
 * 2. 如果左子树为NULL，那么说明其实此时
 * 分支节点的值是最小的。需要删除分支节点。也就是需要将原来的右子树节点代替原来的分支节点.
 */
Node *detach_min(Node **pparent) {
  assert(pparent);
  Node *parent = *pparent;
  if (parent == NULL) {
    return NULL;
  }
  if (parent->left != NULL) {
    return detach_min(&parent->left);
  } else {
    *pparent = parent->right;
    return parent;
  }
}

static bool erase(BSTree *bst, Node **pparent, const void *key) {
  Node *parent = *pparent;
  if (parent == NULL) {
    return false;
  }
  const int cmp_res = bst->cmp(key, bst->key(parent->data));
  if (cmp_res < 0) {
    return erase(bst, &(parent->left), key);
  } else if (cmp_res > 0) {
    return erase(bst, &(parent->right), key);
  } else {
    if (parent->left == NULL) {
      *pparent = parent->right;
    } else if (parent->right == NULL) {
      *pparent = parent->left;
    } else {
      Node *newBranch = detach_min(&(parent->right));
      *pparent = newBranch;
      newBranch->left = parent->left;
      newBranch->right = parent->right;
    }
    free(parent);
    return true;
  }
}

BSTREE_API bool bst_erase(BSTree *bst, const void *key) {
  if (bst == NULL || key == NULL) {
    return false;
  }
  return erase(bst, &(bst->root), key);
}

static bool inorder(Node *parent, bool (*action)(void *data)) {
  int count = 0;
  if (parent == NULL) {
    return 0;
  }
  count = inorder(parent->left, action);
  if (action(parent->data)) {
    count++;
  }
  count += inorder(parent->right, action);
  return count;
}

BSTREE_API int bst_inorder(BSTree *bst, bool (*action)(void *data)) {
  if (bst == NULL || action == NULL) {
    return 0;
  }
  return inorder(bst->root, action);
}