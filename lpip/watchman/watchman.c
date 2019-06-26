#include <codetalks/codetalks.h>
#include <codetalks/inotify_utils.h>
#include <sys/inotify.h>

int main(int argc, char const *argv[]) {
  printf("close event:%s\n", in_mask_to_event_names(IN_CLOSE));
  return 0;
}
