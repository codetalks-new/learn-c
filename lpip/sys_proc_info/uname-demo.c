#include <assert.h>
#include <stdio.h>
#include <sys/utsname.h>

void dump_utsname(struct utsname *u) {
  printf("struct utsname{\n");
  printf("\tsysname(-s)=%s,\n", u->sysname);
  printf("\tnodename(-n)=%s,\n", u->nodename);
  printf("\tversion(-v)=%s,\n", u->version);
  printf("\tmachine(-m)=%s,\n", u->machine);
  printf("\trelease(-r)=%s\n", u->release);
  printf("}\n");
}
int main(int argc, char const *argv[]) {
  struct utsname u;
  int ret = uname(&u);
  assert(ret == 0);
  dump_utsname(&u);

  return 0;
}
