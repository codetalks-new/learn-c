
long answer = 41;
long prices[32] = {1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10};

long imediate_mode() {
  return 41;
}

long register_mode() {
  __asm__("mov $41,%rdi");
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
  *dest = 42;
  return *dest;
}

long base_polonger_mode() {
  long like = 41;
  return like;
}