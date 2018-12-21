/**
 *
 LeetCode 146. LRU缓存机制 C 语言实现 by 代码会说话

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
cache.put(3,3);  // 该操作会使得密钥 2 作废
cache.get(2);     // 返回 -1 (未找到)
cache.put(4, 4);  // 该操作会使得密钥 1 作废
cache.get(1);     // 返回 -1 (未找到)
cache.get(3);     // 返回  3
cache.get(4);     // 返回  4


**后来居上，用之则贵, 末位淘汰**
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
  int capacity;
  int size;
  Entry* head;
} LRUCache;

// Entry, HashMap Node
Entry* makeEntry(int key, int value) {
  Entry* entry = malloc(sizeof(Entry));
  entry->key = key;
  entry->value = value;
  entry->next = NULL;
  return entry;
}

LRUCache* lRUCacheCreate(int capacity) {
  LRUCache* cache = malloc(sizeof(LRUCache));
  cache->size = 0;
  cache->capacity = capacity;
  cache->head = makeEntry(-1, -1);
  assert(capacity > 1);
  return cache;
}

void moveToFront(LRUCache* obj, Entry* entry) {
  // 后来居上
  Entry* prevNode = obj->head->next;
  obj->head->next = entry;
  entry->next = prevNode;
  // head -> 1,2,
}
void removeLastEntry(LRUCache* obj) {
  // 末位淘汰
  // 1,2,3
  Entry* prevNode = obj->head;
  Entry* node = prevNode->next;
  while (node && node->next) {
    prevNode = node;
    node = node->next;
  }
  prevNode->next = NULL;
  free(node);
}

int lRUCacheGet(LRUCache* obj, int key) {
  Entry* prevNode = obj->head;
  Entry* node = obj->head->next;
  while (node != NULL) {
    if (node->key == key) {
      const int value = node->value;
      // 用之则贵
      // 1,2,3,4
      prevNode->next = node->next;
      moveToFront(obj, node);

      return value;
    }
    prevNode = node;
    node = node->next;
  }
  return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
  Entry* entry = makeEntry(key, value);
  // 后来居上
  moveToFront(obj, entry);
  obj->size += 1;
  if (obj->size > obj->capacity) {
    obj->size = obj->capacity;
    removeLastEntry(obj);
  }
}

void lRUCacheFree(LRUCache* obj) {
  Entry* node = obj->head;
  while (node) {
    Entry* tmp = node->next;
    free(node);
    node = tmp;
  }
  free(obj);
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