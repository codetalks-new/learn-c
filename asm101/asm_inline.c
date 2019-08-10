long inline_asm() {
  long src = 1;
  long dst;
  asm("mov %1, %0\n\t"
      "and $1, %0"
      : "=r"(dst)
      : "r"(src));
  return dst;
}