#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <stddef.h>
#include <assert.h>

#include "../vendors/testing/miniunit.h"

int tests_run = 0;

static char * test_strlen(){
  mu_assert("",strlen("abc") == 3);
  const char * t2 = "abc中";
  mu_assert("error,默认多字节字符编码不是UTF-8", strlen(t2) ==6);
  assert(strlen(t2) == 6);
  return 0;
}


static char * test_wcslen_mbstowcs(){
  const char * t2 = "abc中文";
  wchar_t  t3[20]; 
  const size_t len = mbstowcs(t3,t2,6);
  mu_assert("error abc中文 不是5个字符",len == 5);
  mu_assert("", wcslen(L"abc中文") == 5);
  return 0;
}


static char * all_tests(){
  mu_run_test(test_strlen);  
  mu_run_test(test_wcslen_mbstowcs);  
  return 0;
}


int main(int argc, char const *argv[]) {
  char * result = all_tests();
  if(result != 0){
    printf("%s\n", result);
  }else{
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run %d\n", tests_run);
  return result != 0;
}

