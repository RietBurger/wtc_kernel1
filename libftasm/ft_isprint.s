global _ft_isprint

section .text

_ft_isprint:
	cmp		rdi, 32
	jl		exit
	cmp		rdi, 126
	jg		exit
	mov		rax, 1
	ret

exit:
	mov		rax, 0
	ret
