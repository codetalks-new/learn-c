/**
 *
 运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用)
缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

获取数据 get(key) - 如果密钥 (key)
存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。 写入数据 put(key, value)
-
如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

进阶:

你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:

LRUCache cache = new LRUCache( 2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);     // 返回  1
cache.put(3, 3);  // 该操作会使得密钥 2 作废
cache.get(2);     // 返回 -1 (未找到)
cache.put(4, 4);  // 该操作会使得密钥 1 作废
cache.get(1);     // 返回 -1 (未找到)
cache.get(3);     // 返回  3
cache.get(4);     // 返回  4
*
*/

#include <assert.h>
#include <stdlib.h>

typedef struct Entry {
  int key;
  int value;
  struct Entry* next;
} Entry;

typedef struct LRUCache {
  Entry* head;
  int capacity;
  int size;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
  LRUCache* cache = malloc(sizeof(LRUCache));
  cache->size = 0;
  cache->capacity = capacity;
  Entry* head = malloc(sizeof(Entry));
  cache->head = head;
  head->next = NULL;
  head->value = -1;
  head->key = -1;
  return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
  Entry* prevNode = obj->head;
  Entry* node = obj->head->next;
  while (node != NULL) {
    if (node->key == key) {
      const int value = node->value;
      // 将选中的节点移到链表的开始
      prevNode->next = node->next;
      node->next = obj->head->next;
      obj->head->next = node;
      return value;
    }
    prevNode = node;
    node = node->next;
  }
  return -1;
}

void removeLastEntry(LRUCache* obj) {
  Entry* prevNode = obj->head;
  Entry* node = obj->head->next;
  while (node != NULL && node->next != NULL) {
    prevNode = node;
    node = node->next;
  }
  if (prevNode->next != NULL) {
    free(prevNode->next);
  }
  prevNode->next = NULL;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
  Entry* entry = malloc(sizeof(Entry));
  entry->value = value;
  entry->key = key;
  entry->next = NULL;
  // 插件到开头
  Entry* firstNode = obj->head->next;
  entry->next = firstNode;
  obj->head->next = entry;
  obj->size += 1;
  if (obj->size > obj->capacity) {
    obj->size = obj->capacity;
    removeLastEntry(obj);
  }
}

void freeEntries(Entry* head) {
  Entry* node = head;
  while (node != NULL) {
    Entry* tmp = node->next;
    free(node);
    node = tmp;
  }
}

void lRUCacheFree(LRUCache* obj) {
  free(obj);
  freeEntries(obj->head);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * struct LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */

int main() {
  LRUCache* cache = lRUCacheCreate(2);
  lRUCachePut(cache, 1, 1);
  lRUCachePut(cache, 2, 2);
  assert(lRUCacheGet(cache, 1) == 1);
  lRUCachePut(cache, 3, 3);
  assert(lRUCacheGet(cache, 2) == -1);  // 未找到
  lRUCachePut(cache, 4, 4);             // key 1 将被删除
  assert(lRUCacheGet(cache, 1) == -1);  // 未找到
  assert(lRUCacheGet(cache, 3) == 3);
  assert(lRUCacheGet(cache, 4) == 4);

  lRUCacheFree(cache);
  return 0;
}