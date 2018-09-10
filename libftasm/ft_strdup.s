extern _ft_strlen
extern _malloc

global _ft_strdup

section .text

_ft_strdup:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 16
	mov		[rbp -8], rdi
	call _ft_strlen
	cmp		rax, 0
	je		exit
	mov		[rbp -16], rax
	add		rax, 1
	mov		rdi, rax ;set rcx to strlen

mem:
	call	_malloc
	cmp		rax, 0
	je		exit
	mov		rdi, rax
	mov		rsi, [rbp -8]
	mov		rcx, [rbp -16]
	mov		[rbp -16], rdi
	rep		movsb

exit:
	mov		rax, [rbp -16]
	add		rsp, 16
	mov		rsp, rbp
	pop		rbp
	ret
