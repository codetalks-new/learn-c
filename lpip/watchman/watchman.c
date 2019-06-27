#include <codetalks/codetalks.h>
#include <codetalks/inotify_utils.h>
#include <limits.h>
#include <sys/inotify.h>

int main(int argc, char const *argv[]) {
  printf("close event:%s\n", in_mask_to_event_names(IN_CLOSE));
  int inotify_event_max_size =
      10 * sizeof(struct inotify_event) + _PC_NAME_MAX + 1;
  char buf[inotify_event_max_size];
  if (argc < 2 || strcmp(argv[1], "--help") == 0) {
    ct_usage_err("%s pathname... \n", argv[0]);
  }
  int inotify_fd = inotify_init();
  if (inotify_fd == -1) {
    ct_exit("inotify_init");
  }
  for (int i = 1; i < argc; i++) {
    int wd = inotify_add_watch(inotify_fd, argv[i], InotifyMaskAllEvents);
    if (wd == -1) {
      ct_exit("inotify_add_watch");
    }
    printf("Watching %s using %d\n", argv[i], wd);
  }
  for (;;) {
    ssize_t read_cnt = read(inotify_fd, buf, inotify_event_max_size);
    if (read_cnt == 0) {
      ct_fatal("read() from inotify fd returnd 0!");
    }
    if (read_cnt == -1) {
      ct_exit("read");
    }
    printf("Read %ld bytes from inotify fd\n", read_cnt);
    // Process all of the events in buffer returned by read()
    for (char *p = buf; p < buf + read_cnt;) {
      struct inotify_event *event = (struct inotify_event *)p;
      in_log_notify_event(event);
      p += sizeof(struct inotify_event) + event->len;
    }
  }
  return 0;
}
