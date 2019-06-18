#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

void dump_tm(struct tm *tm) {
  printf("struct tm{\n");
  printf("\t tm_sec=%d,\n", tm->tm_sec);
  printf("\t tm_min=%d,\n", tm->tm_min);
  printf("\t tm_hour=%d,\n", tm->tm_hour);
  printf("\t tm_mday=%d,\n", tm->tm_mday);
  printf("\t tm_mon=%d,\n", tm->tm_mon);
  printf("\t tm_year=%d,\n", tm->tm_year);
  printf("\t tm_wday=%d,\n", tm->tm_wday);
  printf("\t tm_yday=%d,\n", tm->tm_yday);
  printf("\t tm_isdst=%d,\n", tm->tm_isdst);
  printf("\t tm_gmtoff=%d,\n", tm->tm_gmtoff);
  printf("\t tm_zone=%s,\n", tm->tm_zone);
  printf("}\n");
}

int main(int argc, char const *argv[]) {
  setlocale(LC_ALL, "");  // 让环境变量的 LC_等值生效.
  printf("固定格式的日期函数,ctime 及 asctime:\n");
  printf("当前时间(ctime):             %s\n", current_time_v1());
  printf("当前时间(gmtime+asctime):    %s\n", current_time_v2());
  printf("当前时间(localtime+asctime): %s\n", current_time_v3());
  printf("自定义格式,本地化\n");
  printf("当前时间(localtime+%%F %%T):      %s\n", current_time_v4("%F %T"));
  printf("当前时间(gmtime+%%F %%T):         %s\n", current_time_v5("%F %T"));
  const time_t now = time(NULL);
  const struct tm *lt = localtime(&now);
  const struct tm *gmt = gmtime(&now);
  printf("localtime:\n");
  dump_tm(lt);
  printf("gmtime:\n");
  dump_tm(gmt);
  return 0;
}

