# 这是一行注释
.global _start
_start:
    mov $0x1, %eax
    mov $0x1, %ebx
    int $0x80
.global main
main:
    nop
    retq
