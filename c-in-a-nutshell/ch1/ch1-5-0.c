#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <wchar.h>
#include <uchar.h>

int main(int argc, char const *argv[]) {
  // const char *text = "aabbccdd中文";
  // printf("%s strlen -> %lu\n", text, strlen(text));
  // const wchar_t *wtext = L"\x3b1";
  // printf("%ls wcslen -> %lu\n", wtext, wcslen(wtext));
  const wchar_t *wtext2 = L"aabbccdd中文";
  wprintf(L"%ls wcslen -> %lu\n", wtext2, wcslen(wtext2));
  const char16_t *wtext3 = u"aabbccdd中文";
  wprintf(L"%ls wcslen -> %lu\n", wtext3, wcslen(wtext3));
  return 0;
}
