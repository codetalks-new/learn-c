#include "bstree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_MAX 1000
char buffer[LEN_MAX];

bool printStr(const *str) { return printf("%s", str) >= 0; }

int main(int argc, char const *argv[]) {
  const BSTree *tree = new_bst((CmpFn *)strcmp, NULL);
  while (fgets(buffer, LEN_MAX, stdin)) {
    size_t len = strlen(buffer);
    if (!bst_insert(tree, buffer, len + 1)) {
      break;
    }
  }
  if (!feof(stdin)) {
    fprintf(stderr, "sortlines:"
                    "Error reading or storing text input\n");
    exit(EXIT_FAILURE);
  }
  int n = bst_inorder(tree, printStr);
  fprintf(stderr, "\nsortlines: Printed %d lines.\n", n);
  bst_clear(tree);
  return 0;
}
