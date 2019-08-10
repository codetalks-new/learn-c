
long answer = 0x29;  // 41
long prices[32] = {1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10};

long imediate_mode() {
  return 0x29;
}

long register_mode() {
  asm("mov $41,%rdi");
  __asm__("mov %rdi,%rax");
  return 0;
}

long direct_mode() {
  return answer;
}

long indexed_mode() {
  int index = 6;
  return prices[index];
}

long indirect_mode() {
  long* dest = &answer;
  *dest = 0x29;
  return *dest;
}

long base_pointer_mode() {
  long like = 0x29;
  return like;
}

#if MAIN
int main() {
  imediate_mode();
  register_mode();
  direct_mode();
  indexed_mode();
  indirect_mode();
  base_pointer_mode();
}

#endif