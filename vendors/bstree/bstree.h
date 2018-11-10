#ifndef BSTREE_H
#define BSTREE_H
#include <assert.h>
#include <stdbool.h> /* Needed for the definition of bool, true,false*/
#include <stdlib.h>  /* calloc funcs */
#include <string.h>  /* Needed for the dfinition of string functions*/

/**
 * Make sure we can call this stuff from C++
 **/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide the ability to override linkage features of the interface.
 */

#ifndef BSTREE_EXTERN
#define BSTREE_EXTERN extern
#endif

#ifndef BSTREE_API
#define BSTREE_API
#endif

#ifndef BSTREE_PRIVATE
#define BSTREE_PRIVATE
#endif

typedef char byte;
// 定义 BST 节点
typedef struct Node {
  // 左子树
  struct Node *left;
  // 右子树
  struct Node *right;
  // 数据的空间大小  （单位：byte）
  size_t size;
  // 数据
  byte data[];
} Node;

// KeyFn 是一个接收一个数据参数的函数， 用于从中提取用于比较的key。相当于 Python 中 sort等函数中的 key 参数
typedef const void *KeyFn(const void *data);
// CmpFn 是一个接收两个数据参数的函数，用于比较两个参数的顺序。如果第一个参数大于第二个则返回1，相等返回0，小于返回-1
typedef int CmpFn(const void *lhs, const void *rhs);

typedef struct {
  // 根节点
  Node *root;
  //  提取数据项key的函数指针
  KeyFn *key;
  // 比较数据项的函数指针
  CmpFn *cmp;
} BSTree;

BSTREE_API BSTree *new_bst(CmpFn *cmp, KeyFn *key);

BSTREE_API bool bst_insert(BSTree *bst, const void *data, size_t size);
BSTREE_API void bst_clear(BSTree *bst);
BSTREE_PRIVATE Node *detach_min(Node **pparent);

BSTREE_API bool bst_erase(BSTree *bst, const void *key);
BSTREE_API int bst_inorder(BSTree *bst, bool (*action)(void *data));

#ifdef __cplusplus
}
#endif

#endif /* end BSTREE_H*/
