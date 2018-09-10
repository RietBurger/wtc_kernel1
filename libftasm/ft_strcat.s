
global _ft_strcat

section .data
null db "NULL"

section .text

_ft_strcat:
	test	rdi, rdi
	je		printZ
	test	rsi, rsi
	xor		rcx, rcx
	push	rdi
	push	rsi

len:
	cmp		BYTE[rdi], 0
	jz		len2
	inc		rdi
	jmp		len

len2:
	cmp		BYTE[rsi], 0
	jz		copy
	inc		rcx
	inc		rsi
	jmp		len2

copy:
	pop		rsi
	inc		rcx
	cld
	rep		movsb

exit:
	pop rax
	ret

printZ:
	mov		rax, 0
	ret
