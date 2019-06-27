#pragma once
#include <time.h>

char *ct_current_time(const char *format) {
  const time_t now = time(NULL);
  const struct tm *t = localtime(&now);
  static char buf[32] = {'\0'};
  strftime(buf, sizeof(buf), format, t);
  return buf;
}

char *ct_current_datetime_isoformat() {
  return ct_current_time("%F %T");
}