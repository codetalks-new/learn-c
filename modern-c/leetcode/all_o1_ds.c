/**
 *
LeetCode 432. 全 O(1) 的数据结构 -by 代码会说话
实现一个数据结构支持以下操作：

Inc(key) - 插入一个新的值为 1 的 key。或者使一个存在的 key 增加一，保证 key
不为空字符串。 Dec(key) - 如果这个 key 的值是
1，那么把他从数据结构中移除掉。否者使一个存在的 key 值减一。如果这个 key
不存在，这个函数不做任何事情。key 保证不为空字符串。 GetMaxKey() - 返回 key
中值最大的任意一个。如果没有元素存在，返回一个空字符串""。 GetMinKey() - 返回
key 中值最小的任意一个。如果没有元素存在，返回一个空字符串""。 挑战：以 O(1)
的时间复杂度实现所有操作。
 *
 */
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
  char* key;
  int value;
  struct KeyValue* next;
  struct KeyValue* prev;
} KeyValue;

KeyValue* new_key_value(char* key) {
  KeyValue* kv = malloc(sizeof(KeyValue));
  kv->key = strdup(key);
  kv->value = 1;
  kv->next = NULL;
  kv->prev = NULL;
  return kv;
}
/**
 * 有序单链表
 *
 */
typedef struct AllOne {
  KeyValue* head;  // 头节点不包含数据
  KeyValue* last;  // 指向最后一个节点,同时也是最小值节点
} AllOne;

#define EQ(a, b) (strcmp((a), (b)) == 0)

/** Initialize your data structure here. */
AllOne* allOneCreate() {
  AllOne* obj = malloc(sizeof(AllOne));
  obj->head = new_key_value("");
  obj->last = NULL;
  return obj;
}

/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
void allOneInc(AllOne* obj, char* key) {
  if (obj->last == NULL) {
    // 第一个节点
    KeyValue* first = new_key_value(key);

    obj->head->next = first;
    obj->last = first;
    return;
  } else {
    // 非首次节点
    KeyValue* cur = obj->head->next;
    bool found = false;
    while (cur) {
      if (EQ(cur->key, key)) {
        cur->value += 1;
        found = true;
        break;
      }
      cur = cur->next;
    }
    if (found) {
      // 如果有匹配，看能否前移
      KeyValue* old_prev = cur->prev;
      KeyValue* old_next = cur->next;
      KeyValue* p = cur->prev;
      bool moved = false;
      while (p) {
        if (p->value < cur->value) {
          p = p->prev;
          moved = true;
        } else {
          break;
        }
      }
      if (p && moved) {
        if (cur == obj->last) {
          obj->last = old_prev;
        }
        old_prev->next = old_next;
        if (old_next) {
          old_next->prev = old_prev;
        }
        cur->next = p->next;
        p->next->prev = cur;
        p->next = cur;
        cur->prev = p;
      }
    } else {
      // 如果没有匹配的节点，说明是新的节点
      KeyValue* new_kv = new_key_value(key);
      obj->last->next = new_kv;
      new_kv->prev = obj->last;
      obj->last = new_kv;
    }
  }
}

/** Decrements an existing key by 1. If Key's value is 1, remove it from the
 * data structure. */
void allOneDec(AllOne* obj, char* key) {
  KeyValue* cur = obj->head->next;
  while (cur) {
    if (EQ(cur->key, key)) {
      cur->value -= 1;
      if (cur->value == 0) {
        KeyValue* prev = cur->prev;
        if (cur->next == NULL) {  // 最后一个节点
          if (prev == NULL) {
            // 第一个节点
            obj->head->next = NULL;
            obj->last = NULL;
          } else {
            obj->last = prev;
            prev->next = NULL;
          }
        } else {
          // 由于有序,所以不应该是第一个节点
          assert(prev);
          prev->next = cur->next;
          cur->next->prev = prev;
        }
        free(cur);
      } else {
        // 向右移到
        KeyValue* p = cur->next;
        bool moved = false;
        while (p) {
          if (p->value > cur->value) {
            p = p->next;
            moved = true;
          } else {
            break;
          }
        }
        if (p && moved) {
          KeyValue* prev = cur->prev;
          KeyValue* next = cur->next;
          if (prev == NULL) {
            // 说明是第一个节点
            KeyValue* new_first = cur->next;
            obj->head->next = new_first;
            new_first->prev = NULL;
          } else {
            prev->next = next;
            next->prev = prev;
          }
          cur->next = p;
          p->prev = cur;
        }
      }
      break;
    }
    cur = cur->next;
  }
}

/** Returns one of the keys with maximal value. */
char* allOneGetMaxKey(AllOne* obj) {
  assert(obj->head->next);
  return obj->head->next->key;
}

/** Returns one of the keys with Minimal value. */
char* allOneGetMinKey(AllOne* obj) {
  assert(obj->last);
  return obj->last->key;
}

void allOneFree(AllOne* obj) {}

/**
 * Your AllOne struct will be instantiated and called as such:
 * struct AllOne* obj = allOneCreate();
 * allOneInc(obj, key);
 * allOneDec(obj, key);
 * char* param_3 = allOneGetMaxKey(obj);
 * char* param_4 = allOneGetMinKey(obj);
 * allOneFree(obj);
 */
int main() {
  AllOne* obj = allOneCreate();
  allOneInc(obj, "san");
  assert(EQ(allOneGetMaxKey(obj), "san"));
  assert(EQ(allOneGetMinKey(obj), "san"));
  allOneInc(obj, "san");
  allOneInc(obj, "yan");
  assert(EQ(allOneGetMaxKey(obj), "san"));
  assert(EQ(allOneGetMinKey(obj), "yan"));
  allOneDec(obj, "yan");
  assert(EQ(allOneGetMaxKey(obj), "san"));
  assert(EQ(allOneGetMinKey(obj), "san"));
  return 0;
}