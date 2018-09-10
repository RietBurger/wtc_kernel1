global _ft_tolower

section .text

_ft_tolower:
	cmp		rdi, 'A'
	jl		exit
	cmp		rdi, 'Z'
	jg		exit
	add		rdi, 32
	mov		rax, rdi
	ret

exit:
	mov		rax, rdi
	ret
