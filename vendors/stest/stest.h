#ifndef STEST_H
#define STEST_H
#include <assert.h>
#include <stdbool.h> /* Needed for the definition of bool, true,false*/
#include <string.h> /* Needed for the dfinition of string functions*/

/**
 * Make sure we can call this stuff from C++
 **/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide the ability to override linkage features of the interface.
 */

#ifndef STEST_EXTERN
#define STEST_EXTERN extern
#endif

#ifndef STEST_API
#define STEST_API
#endif

STEST_API bool assert_str_eq(const char *str1,const char *str2){
  if(str1 == NULL || str2 == NULL){
    assert(false);
    return false;
  }
  const int result = strcmp(str1, str2);
  assert(result == 0);
  return result == 0;
}

#ifdef __cplusplus
}
#endif

#endif




