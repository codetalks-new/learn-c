#include <stdint.h>
#define X_TO_Y(xtype, ytype)                                        \
  void convert_##xtype##_ptr_to_##ytype##_ptr(xtype *x, ytype *y) { \
    *y = (ytype)*x;                                                 \
  }

X_TO_Y(long, long);
X_TO_Y(char, int);
X_TO_Y(char, unsigned);
X_TO_Y(uint8_t, long);
X_TO_Y(int, char);
X_TO_Y(unsigned, uint8_t);
X_TO_Y(char, short);

/**
 *


0000000000000000 <convert_long_ptr_to_long_ptr>:
   0:   48 8b 07                mov    (%rdi),%rax
   3:   48 89 06                mov    %rax,(%rsi)
   6:   c3                      retq

0000000000000007 <convert_char_ptr_to_int_ptr>:
   7:   0f be 07                movsbl (%rdi),%eax
   a:   89 06                   mov    %eax,(%rsi)
   c:   c3                      retq

000000000000000d <convert_char_ptr_to_unsigned_ptr>:
   d:   0f be 07                movsbl (%rdi),%eax
  10:   89 06                   mov    %eax,(%rsi)
  12:   c3                      retq

0000000000000013 <convert_uint8_t_ptr_to_long_ptr>:
  13:   0f b6 07                movzbl (%rdi),%eax
  16:   48 89 06                mov    %rax,(%rsi)
  19:   c3                      retq

000000000000001a <convert_int_ptr_to_char_ptr>:
  1a:   8b 07                   mov    (%rdi),%eax
  1c:   88 06                   mov    %al,(%rsi)
  1e:   c3                      retq

000000000000001f <convert_unsigned_ptr_to_uint8_t_ptr>:
  1f:   8b 07                   mov    (%rdi),%eax
  21:   88 06                   mov    %al,(%rsi)
  23:   c3                      retq

0000000000000024 <convert_char_ptr_to_short_ptr>:
  24:   66 0f be 07             movsbw (%rdi),%ax
  28:   66 89 06                mov    %ax,(%rsi)
  2b:   c3                      retq

 *
 */