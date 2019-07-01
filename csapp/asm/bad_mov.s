.global _start
_start:
  movb $0xf, (%ebx)
  movl %rax,(%rsp) # incorrect register `%rax` used with `l` suffix
  movw (%rax), 4(%rsp) # too many memory references for `mov`
  movb %al, %sl  # bad register name `%sl`
  movq %rax ,$0x123 # operand type mismatch for `movq`
  movl %eax, %rdx # unsupported instruction `mov`
  movb %si, 8(%rbp) # `%si` not allowed with `movb`
