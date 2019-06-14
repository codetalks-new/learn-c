#include <assert.h>
#include "list.h"

int main(int argc, char const *argv[]) {
  LIST_HEAD(scores);
  assert(scores.next == scores.prev);
  return 0;
}
