%define SYSCAL(n) 0x2000000|n
%define STDOUT 1

global _ft_cat

section .data
succ db "success", 10


section .bss
buff resb 4096


section .text

_ft_cat:
	cmp		rdi, 0
	jl		sysexit

read:
	push	rdi
	mov		rsi, buff
	mov		rdx, 4096
	mov		rax, SYSCAL(3); READ
	syscall

	jc		exitC
	cmp		rax, 0
	jle		exitC

write:
	mov		rdx, rax
	mov		rsi, buff
	mov		rdi, 1
	mov		rax, SYSCAL(4);write
	syscall

exit:
	pop		rdi
	jmp		read

exitC:
	pop		rdi
	mov		rax, SYSCAL(3)
	syscall

sysexit:
	ret
