#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Linux C语言 系统编程实践 (2) 环境变量
// - by 代码会说话
// 增: setenv(name,value,overriding), putenv; shell 中 export NAME=Value
// 删除 : unsetenv  ;在 shell 里面使用 unset NAME
// 改: setenv(name,value, overriding) 最后一个参数
// 查: getenv  ; 在 shell 里中 $NAME 的方式引用. 用 echo $NAME
// SHELL -> env_demo
//       -> printenv
// POSIX

typedef char* str;
extern char** environ;

void print_env() {
  for (char** env = environ; env && *env != NULL; env++) {
    printf("%s\n", *env);
  }
  printf("环境变量如上!\n");
}

int main(int argc, char const* argv[]) {
  unsetenv("YOUQUE_STORE_PASSWORD");
  setenv("YOUQUE_KEY_PASSWORD", "", 1);
  setenv("YOUQUE_ANDROID_SECRET_KEY", "", 1);
  setenv("AUTHOR", "codetalks", 0);
  putenv("DEBUG=1");
  print_env();
  printf("当前作者是:%s\n", getenv("AUTHOR"));
  printf("当前用户是:%s\n", getenv("USER"));
  return 0;
}
