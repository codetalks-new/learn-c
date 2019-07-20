#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

/**
 *  POSIX 选项定义在 <limits.h> 头文件中,以 _POSIX
 */
typedef enum PosixOptionType {
  PosixOptionNotSupported = -1,
  PosixOptionAskAtRuntime = 0,
  PosixOptionSince = 1,  // 非-1和0值.
} PosixOptionType;

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
