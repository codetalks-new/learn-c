void decode1(long *xp, long *yp, long *zp) {
  long x = *xp;
  long y = *yp;
  long z = *zp;

  *yp = x;
  *zp = y;
  *xp = z;
}
void decode2(long *xp, long *yp, long *zp) {
  *yp = *xp;
  *zp = *yp;
  *xp = *zp;
}
/**
 *
 *
 0000000000000000 <decode1>:
   0:   4c 8b 07                mov    (%rdi),%r8
   3:   48 8b 0e                mov    (%rsi),%rcx
   6:   48 8b 02                mov    (%rdx),%rax
   9:   4c 89 06                mov    %r8,(%rsi)
   c:   48 89 0a                mov    %rcx,(%rdx)
   f:   48 89 07                mov    %rax,(%rdi)
  12:   c3                      retq

0000000000000013 <decode2>:
  13:   48 8b 07                mov    (%rdi),%rax
  16:   48 89 06                mov    %rax,(%rsi)
  19:   48 89 02                mov    %rax,(%rdx)
  1c:   48 89 07                mov    %rax,(%rdi)
  1f:   c3                      retq

 */