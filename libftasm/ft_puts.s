%define WRITE(n) 0x2000000|n

global _ft_puts

section .data
null db "NULL"

section .text
_ft_puts:
	test	rdi, rdi
	jz		printZ

	mov		rsi, rdi

	xor		rcx, rcx

len:
	cmp		BYTE[rdi], 0
	je		write
	inc		rcx; holds str len
	inc		rdi
	jmp		len

write:
	mov		rdi, 1 ;STDOUT
 	mov		rdx, rcx ;count at rdx
	mov		rax, WRITE(4)
	syscall
	jmp		exit

printZ:
	mov		rdi, 1
	mov		rdx, 4
	mov		rsi, null
	mov		rax, WRITE(4)
	syscall

exit:
	ret
