# 汇编调用标准库输出 Hello World
.section .data
greetings:
    .ascii "Hello World\n\0"
.section .text
.global _start
_start:
    push $greetings
    call printf
    push $0
    call exit

    
