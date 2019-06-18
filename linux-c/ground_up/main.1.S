.global _start
_start:
    mov $1, %eax # $1 表示字面量1, linux 对于系统调用从 %eax 寄存器中读取对应值
    mov $0, %ebx # %ebx 用于保存系统调用退出时的状态码
    int $0x80  # 0x80 中断通知CPU切换为到内核执行太,也就是让操作系统执行系统调用
