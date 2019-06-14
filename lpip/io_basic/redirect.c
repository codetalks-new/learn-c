#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// stdin 0
// stdout 1
// stderr 2
// 1 -> /dev/tty0
// 1 -> output.txt
// 2 -> output.txt
// /dev/stdin/
//
int main(int argc, char const* argv[]) {
  fprintf(stdout, "参数个数:%d\n", argc);
  fprintf(stdout, "输出到标准输出\n");
  // int fd = open("/dev/fd/0", 0);
  char buf[1024];
  // int read_cnt = read(fd, buf, sizeof 1024);
  // int read_cnt = fread(buf, 1, sizeof buf, stdin);
  // fprintf(stdout, "(read:%d) %s\n", read_cnt, buf);
  // write(STDOUT_FILENO, "输出到标准输出\n", 23);
  fprintf(stderr, "输出到标准错误输出\n");
  // write(STDERR_FILENO, "输出到标准错误输出\n", 29);
  // getchar();
  return 0;
}
