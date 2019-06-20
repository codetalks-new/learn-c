#include <fcntl.h> /* O_RDONLY etc file flag and mode */
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  fd_set watched_fds;
  int fd_yktv = open('yktv.tmp', O_RDONLY);
  int fd_mgtv = open('mgtv.tmp', O_RDONLY);
  int fd_qqtv = open('qqtv.tmp', O_RDONLY);
  do {
    FD_ZERO(&watched_fds);
    FD_SET(fd_yktv, &watched_fds);
    FD_SET(fd_mgtv, &watched_fds);
    FD_SET(fd_qqtv, &watched_fds);

  } while (true);

  return 0;
}
