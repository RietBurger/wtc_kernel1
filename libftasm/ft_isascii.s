global _ft_isascii

section .text

_ft_isascii:
	cmp		rdi, 0
	jl		exit
	cmp		rdi, 127
	jg		exit
	mov		rax, 1
	ret

exit:
	mov		rax, 0
	ret
