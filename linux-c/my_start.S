.global _start
_start:
    callq main
    mov $0x1, %eax
    mov $0x1, %ebx
    int $0x80
