#include <stdint.h>
#define S_TO_D(src_type, dst_type)                            \
  dst_type src_type##_to_##dst_type(src_type a, dst_type b) { \
    return (dst_type)a;                                       \
  };
// 有符号到有符号
S_TO_D(int8_t, int8_t);    // movl %edi,%rax
S_TO_D(int8_t, int16_t);   // movl %edi, %rax
S_TO_D(int8_t, int32_t);   // movl %edi,%rax
S_TO_D(int8_t, int64_t);   // movslq %edi, %rax
S_TO_D(int16_t, int8_t);   // movsbl %dil, %eax
S_TO_D(int16_t, int16_t);  // movl %edi,%rax
S_TO_D(int16_t, int32_t);  // movl %edi,%eax
S_TO_D(int16_t, int64_t);  // movslq %edi,%rax
S_TO_D(int32_t, int8_t);   // movsbl %dil, %eax
S_TO_D(int32_t, int16_t);  // movswl %di,%eax
S_TO_D(int32_t, int32_t);  // movl %edi, %eax
S_TO_D(int32_t, int64_t);  // movslq %edi, %rax
S_TO_D(int64_t, int8_t);   // movsbl %dil,%eax
S_TO_D(int64_t, int16_t);  //  movswl %di, %eax
S_TO_D(int64_t, int32_t);  // movl %edi,%eax
S_TO_D(int64_t, int64_t);  // movq %rdi,%rax
// 有符号到无符号
S_TO_D(int8_t, uint8_t);   // movzbl %dil, %eax
S_TO_D(int8_t, uint16_t);  // movzwl %di, %eax
S_TO_D(int8_t, uint32_t);  // movl %edi, %eax
S_TO_D(int8_t, uint64_t);  // movslq %edi, %rax
S_TO_D(int16_t, uint8_t);  //
S_TO_D(int16_t, uint16_t);
S_TO_D(int16_t, uint32_t);
S_TO_D(int16_t, uint64_t);
S_TO_D(int32_t, uint8_t);
S_TO_D(int32_t, uint16_t);
S_TO_D(int32_t, uint32_t);
S_TO_D(int32_t, uint64_t);
S_TO_D(int64_t, uint8_t);
S_TO_D(int64_t, uint16_t);
S_TO_D(int64_t, uint32_t);
S_TO_D(int64_t, uint64_t);

// 无符号到有符号
S_TO_D(uint8_t, int8_t);   // movsbl %dil, %eax
S_TO_D(uint8_t, int16_t);  // movl %edi, %eax
S_TO_D(uint8_t, int32_t);  // movl %edi, %eax
S_TO_D(uint8_t, int64_t);  // movl %edi, %eax
S_TO_D(uint16_t, int8_t);  // movsbl %dil, %eax
S_TO_D(uint16_t, int16_t);
S_TO_D(uint16_t, int32_t);
S_TO_D(uint16_t, int64_t);
S_TO_D(uint32_t, int8_t);
S_TO_D(uint32_t, int16_t);
S_TO_D(uint32_t, int32_t);
S_TO_D(uint32_t, int64_t);
S_TO_D(uint64_t, int8_t);
S_TO_D(uint64_t, int16_t);
S_TO_D(uint64_t, int32_t);
S_TO_D(uint64_t, int64_t);

// 无符号到无符号
S_TO_D(uint8_t, uint8_t);   // movl %edi, %eax
S_TO_D(uint8_t, uint16_t);  // movl %edi, %eax
S_TO_D(uint8_t, uint32_t);
S_TO_D(uint8_t, uint64_t);
S_TO_D(uint16_t, uint8_t);   // movzbl %dil, %eax
S_TO_D(uint16_t, uint16_t);  // movl %edi, %eax
S_TO_D(uint16_t, uint32_t);
S_TO_D(uint16_t, uint64_t);
S_TO_D(uint32_t, uint8_t);
S_TO_D(uint32_t, uint16_t);  // movzwl %di,%eax
S_TO_D(uint32_t, uint32_t);
S_TO_D(uint32_t, uint64_t);
S_TO_D(uint64_t, uint8_t);   // movzbl %dil, %eax
S_TO_D(uint64_t, uint16_t);  // movzwl %di,%eax
S_TO_D(uint64_t, uint32_t);  // movl %edi, %eax
S_TO_D(uint64_t, uint64_t);

void debug_mov_x() {
  // from csapp page 124
  __asm__("movabsq $0x0011223344556677,%rax");
  __asm__("movb $-1,%al");  // 0xff
  __asm__("movw $-1,%ax");
  __asm__("movl $-1,%eax");
  asm("movq $-1,%rax");
}

#if MAIN
int main(int argc, char const *argv[]) {
  debug_mov_x();
  return 0;
}

#endif