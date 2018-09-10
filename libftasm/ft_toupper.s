global _ft_toupper

section .text

_ft_toupper:
	cmp		rdi, 'a'
	jl		exit
	cmp		rdi, 'z'
	jg		exit
	sub		rdi, 32
	mov		rax, rdi
	ret

exit:
	mov		rax, rdi
	ret
