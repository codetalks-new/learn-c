	.file	"type_convert_move.c"
	.text
	.globl	convert_long_ptr_to_long_ptr
	.type	convert_long_ptr_to_long_ptr, @function
convert_long_ptr_to_long_ptr:
.LFB0:
	.cfi_startproc
	movq	(%rdi), %rax
	movq	%rax, (%rsi)
	ret
	.cfi_endproc
.LFE0:
	.size	convert_long_ptr_to_long_ptr, .-convert_long_ptr_to_long_ptr
	.globl	convert_char_ptr_to_int_ptr
	.type	convert_char_ptr_to_int_ptr, @function
convert_char_ptr_to_int_ptr:
.LFB1:
	.cfi_startproc
	movsbl	(%rdi), %eax
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE1:
	.size	convert_char_ptr_to_int_ptr, .-convert_char_ptr_to_int_ptr
	.globl	convert_char_ptr_to_unsigned_ptr
	.type	convert_char_ptr_to_unsigned_ptr, @function
convert_char_ptr_to_unsigned_ptr:
.LFB2:
	.cfi_startproc
	movsbl	(%rdi), %eax
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE2:
	.size	convert_char_ptr_to_unsigned_ptr, .-convert_char_ptr_to_unsigned_ptr
	.globl	convert_uint8_t_ptr_to_long_ptr
	.type	convert_uint8_t_ptr_to_long_ptr, @function
convert_uint8_t_ptr_to_long_ptr:
.LFB3:
	.cfi_startproc
	movzbl	(%rdi), %eax
	movq	%rax, (%rsi)
	ret
	.cfi_endproc
.LFE3:
	.size	convert_uint8_t_ptr_to_long_ptr, .-convert_uint8_t_ptr_to_long_ptr
	.globl	convert_int_ptr_to_char_ptr
	.type	convert_int_ptr_to_char_ptr, @function
convert_int_ptr_to_char_ptr:
.LFB4:
	.cfi_startproc
	movl	(%rdi), %eax
	movb	%al, (%rsi)
	ret
	.cfi_endproc
.LFE4:
	.size	convert_int_ptr_to_char_ptr, .-convert_int_ptr_to_char_ptr
	.globl	convert_unsigned_ptr_to_uint8_t_ptr
	.type	convert_unsigned_ptr_to_uint8_t_ptr, @function
convert_unsigned_ptr_to_uint8_t_ptr:
.LFB5:
	.cfi_startproc
	movl	(%rdi), %eax
	movb	%al, (%rsi)
	ret
	.cfi_endproc
.LFE5:
	.size	convert_unsigned_ptr_to_uint8_t_ptr, .-convert_unsigned_ptr_to_uint8_t_ptr
	.globl	convert_char_ptr_to_short_ptr
	.type	convert_char_ptr_to_short_ptr, @function
convert_char_ptr_to_short_ptr:
.LFB6:
	.cfi_startproc
	movsbw	(%rdi), %ax
	movw	%ax, (%rsi)
	ret
	.cfi_endproc
.LFE6:
	.size	convert_char_ptr_to_short_ptr, .-convert_char_ptr_to_short_ptr
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
