.text
	.globl _start

_start:
	xor %rbp,%rbp
	pop %rdi
	mov %rsp,%rsi
	and $-0xF,%rsp
	call main

	mov %rax,%rdi
	mov $60,%rax
	syscall

	ret
