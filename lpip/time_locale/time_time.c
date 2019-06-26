#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

char *current_time_v1() {
  const time_t now = time(NULL);
  return ctime(&now);
}

char *current_time_v2() {
  const time_t now = time(NULL);
  const struct tm *gmtm = gmtime(&now);
  return asctime(gmtm);
}

char *current_time_v3() {
  const time_t now = time(NULL);
  const struct tm *tm = localtime(&now);
  return asctime(tm);
}

char *current_time_v4(const char *format) {
  const time_t now = time(NULL);
  const struct tm *tm = localtime(&now);
  static char out_str[128];
  strftime(out_str, sizeof(out_str), format, tm);
  return out_str;
}

char *current_time_v5(const char *format) {
  const time_t now = time(NULL);
  const struct tm *tm = gmtime(&now);
  static char out_str[128];
  strftime(out_str, sizeof(out_str), format, tm);
  return out_str;
}

void dump_tm(const struct tm *tm) {
  printf("struct tm {\n");
  printf("\t tm_sec=%d,\n", tm->tm_sec);
  printf("\t tm_min=%d,\n", tm->tm_min);
  printf("\t tm_hour=%d,\n", tm->tm_hour);
  printf("\t tm_mday=%d,\n", tm->tm_mday);
  printf("\t tm_mon=%d,\n", tm->tm_mon);
  printf("\t tm_year=%d,\n", tm->tm_year);
  printf("\t tm_wday=%d,\n", tm->tm_wday);
  printf("\t tm_yday=%d,\n", tm->tm_yday);
  printf("\t tm_isdst=%d,\n", tm->tm_isdst);
  printf("\t tm_gmtoff=%ld,\n", tm->tm_gmtoff);
  printf("\t tm_tone=%s,\n", tm->tm_zone);
  printf("}\n");
}

void dump_timeval(const struct timeval *tv) {
  printf("struct timeval {\n");
  printf("\t tv_sec=%ld\n", tv->tv_sec);
  printf("\t tv_usec=%d\n", tv->tv_usec);
  printf("}\n");
}

int main(int argc, char const *argv[]) {
  const time_t t = time(NULL);
  struct timeval tv;
  gettimeofday(&tv, NULL);
  printf("time_t t = %ld\n", t);
  dump_timeval(&tv);

  setlocale(LC_ALL, "");  // 让环境变量的 LC_等值生效.
  printf("固定格式的日期函数,ctime 及 asctime:\n");
  printf("当前时间(ctime):             %s\n", current_time_v1());
  printf("当前时间(gmtime+asctime):    %s\n", current_time_v2());
  printf("当前时间(localtime+asctime): %s\n", current_time_v3());
  printf("自定义格式,本地化\n");
  printf("当前时间(localtime+%%F %%T):      %s\n", current_time_v4("%F %T"));
  printf("当前时间(gmtime+%%F %%T):         %s\n", current_time_v5("%F %T"));
  printf("当前时间(localtime+%%x %%X):      %s\n", current_time_v4("%x %X"));
  printf("当前时间(gmtime+%%x %%X):         %s\n", current_time_v5("%x %X"));
  const time_t now = time(NULL);
  struct tm *lt = localtime(&now);
  // const time_t now_ret = mktime(lt);
  // printf("localtime now_ret:%ld\n", now_ret);
  // struct tm gmt;
  // gmtime_r(&now, &gmt);
  printf("localtime:\n");
  dump_tm(lt);
  // printf("gmtime:\n");
  // dump_tm(&gmt);
  // sleep(3);
  // time_t seconds_later = time(NULL);

  // gmtime(&seconds_later);
  // dump_tm(&gmt);

  return 0;
}
