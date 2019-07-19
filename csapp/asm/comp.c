#define CMP(type, memo, cmp)                \
  int cmp_##type##_##memo(type a, type b) { \
    return a cmp b;                         \
  }

#define UCMP(type, memo, cmp)                                          \
  int cmp_unsigned_##type##_##memo(unsigned type a, unsigned type b) { \
    return a cmp b;                                                    \
  }

CMP(long, lt, <)
CMP(long, le, <=)
CMP(long, eq, ==)
CMP(long, gt, >)
CMP(long, gte, >=)
UCMP(long, lt, <)
UCMP(long, le, <=)
UCMP(long, eq, ==)
UCMP(long, gt, >)
UCMP(long, gte, >=)

/**
 *
 * 生成的汇编节选
 * clang -std=c11 csapp/asm/comp.c -c -O1 -o comp.o && objdump -d comp.o

_cmp_long_le:
      10:       55      pushq   %rbp
      11:       48 89 e5        movq    %rsp, %rbp
      14:       31 c0   xorl    %eax, %eax
      16:       48 39 f7        cmpq    %rsi, %rdi
      19:       0f 9e c0        setle   %al
      1c:       5d      popq    %rbp
      1d:       c3      retq
      1e:       66 90   nop

_cmp_unsigned_long_gt:
      80:       55      pushq   %rbp
      81:       48 89 e5        movq    %rsp, %rbp
      84:       31 c0   xorl    %eax, %eax
      86:       48 39 f7        cmpq    %rsi, %rdi
      89:       0f 97 c0        seta    %al
      8c:       5d      popq    %rbp
      8d:       c3      retq
      8e:       66 90   nop
 */