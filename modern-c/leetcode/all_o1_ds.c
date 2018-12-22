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

typedef enum Direction { NEXT, PREV } Direction;

void deleteKeyValue(AllOne* obj, KeyValue* kv) {
  const bool is_first = kv->prev == NULL;
  const bool is_last = kv->next == NULL;
  if (is_first && is_last) {
    obj->head->next = NULL;
    obj->last = NULL;
  } else if (is_last) {
    KeyValue* prev = kv->prev;
    obj->last = prev;
    prev->next = NULL;
  } else if (is_first) {
    KeyValue* next = kv->next;
    next->prev = NULL;
    obj->head->next = next;
  } else {
    KeyValue* prev = kv->prev;
    KeyValue* next = kv->next;
    prev->next = next;
    next->prev = prev;
  }
  free(kv);
}

/**
 * 向前或向后遍历查找要移到到的目标位置
 * 方向是向前时：
 * 返回点的值大于或者等于目标值，为了统一向返回点的右边插件，所以返回点有可能是要插入点本身。此时可以不插入。
 *  如果返回 NULL，说明要移到动尾部
 * 方向上向后时： 返回点的值是大于或者等于目标值，如果返回 NULL,
 * 说明要移动到头部
 *
 */
KeyValue* findDestPrev(KeyValue* cur, Direction dir) {
  KeyValue* p = dir == NEXT ? cur->next : cur->prev;
  while (p) {
    if (dir == NEXT) {
      if (p->value > cur->value) {
        if (p->next == NULL) {
          return p;
        }
        p = p->next;
      } else {
        return p->prev;
      }
    } else {
      if (p->value < cur->value) {
        p = p->prev;
      } else {
        return p;
      }
    }
  }
  return NULL;
}

void moveTo(AllOne* obj, KeyValue* cur, Direction dir) {
  // 向右移到
  KeyValue* destPrev = findDestPrev(cur, dir);
  if (destPrev == cur) {
    return;
  }
  // 1) 旧关系的断裂
  KeyValue* old_prev = cur->prev;
  KeyValue* old_next = cur->next;
  assert(old_prev || old_next);
  if (old_prev && old_next) {
    old_prev->next = old_next;
    old_next->prev = old_prev;
  } else if (old_prev == NULL) {
    // cur 原来是头节点，现在向右移动
    obj->head->next = destPrev;
    destPrev->prev = NULL;
  } else if (old_next == NULL) {
    // cur 原来是尾节点，现在向左移动
    old_prev->next = NULL;
    obj->last = old_prev;
  }
  // 2) 新关系的建立
  if (destPrev == NULL) {
    destPrev = obj->head;
  }
  cur->next = destPrev->next;
  if (cur->next == NULL) {
    obj->last = cur;
  }
  if (destPrev->next) {
    destPrev->next->prev = cur;
  }
  destPrev->next = cur;
  cur->prev = destPrev;
  obj->head->next->prev = NULL;
  int wait = 0;
}

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
      if (cur->prev != NULL) {
        moveTo(obj, cur, PREV);
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
        deleteKeyValue(obj, cur);
      } else {
        if (cur->next != NULL) {
          moveTo(obj, cur, NEXT);
        }
      }
      break;
    }
    cur = cur->next;
  }
}

/** Returns one of the keys with maximal value. */
char* allOneGetMaxKey(AllOne* obj) {
  const KeyValue* max = obj->head->next;
  return max ? max->key : "";
}

/** Returns one of the keys with Minimal value. */
char* allOneGetMinKey(AllOne* obj) {
  return obj->last ? obj->last->key : "";
}

void allOneFree(AllOne* obj) {
  KeyValue* kv = obj->head;
  while (kv) {
    KeyValue* tmp = kv;
    kv = kv->next;
    free(tmp);
  }
  free(obj);
}

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
  // Runtime Error 2
  AllOne* a3 = allOneCreate();
  allOneInc(a3, "a");
  allOneInc(a3, "b");
  allOneInc(a3, "c");
  allOneInc(a3, "d");
  allOneInc(a3, "a");
  allOneInc(a3, "b");
  allOneInc(a3, "c");
  allOneInc(a3, "d");
  allOneInc(a3, "c");
  allOneInc(a3, "d");
  allOneInc(a3, "d");
  allOneInc(a3, "a");
  assert(EQ(allOneGetMinKey(a3), "b"));
  // Runtime Error 1
  AllOne* a2 = allOneCreate();
  allOneInc(a2, "a");
  allOneInc(a2, "b");
  allOneInc(a2, "b");
  allOneInc(a2, "c");
  allOneInc(a2, "c");
  allOneInc(a2, "c");
  allOneDec(a2, "b");
  allOneDec(a2, "b");
  assert(EQ(allOneGetMinKey(a2), "a"));
  allOneDec(a2, "a");
  assert(EQ(allOneGetMaxKey(a2), "c"));
  assert(EQ(allOneGetMinKey(a2), "c"));
  // 超时测试1
  AllOne* a1 = allOneCreate();
  allOneInc(a1, "hello");
  allOneInc(a1, "goodbye");
  allOneInc(a1, "hello");
  allOneInc(a1, "hello");
  assert(EQ(allOneGetMaxKey(a1), "hello"));
  allOneInc(a1, "leet");
  allOneInc(a1, "code");
  allOneInc(a1, "leet");
  allOneDec(a1, "hello");
  allOneInc(a1, "leet");
  allOneInc(a1, "code");
  allOneInc(a1, "code");
  assert(EQ(allOneGetMaxKey(a1), "leet"));
  // 示例测试
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
  allOneFree(obj);
  // 测试只有一个
  AllOne* obj2 = allOneCreate();
  allOneInc(obj2, "san");
  allOneDec(obj2, "san");
  assert(EQ(allOneGetMinKey(obj2), ""));
  assert(EQ(allOneGetMaxKey(obj2), ""));
  allOneFree(obj2);

  return 0;
}