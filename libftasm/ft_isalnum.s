extern _ft_isalpha

global _ft_isalnum

section .text

_ft_isalnum:

	cmp		rdi, '0'
	jl		exit
	cmp		rdi, '9'
	jg		alpha
	mov		rax, 1
	ret

alpha:

	call	_ft_isalpha
	cmp		rax, 0
	je		exit
	mov		rax, 1
	ret

exit:
	mov		rax, 0
	ret
