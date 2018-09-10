global _ft_strlen

section .text
_ft_strlen:
	sub rcx, rcx
	not rcx ;set rcx = -1 (biggest possible nr)

	xor rax, rax ;set rax to 0
	cld ;clear direction flag: reverse read order, which is now left to right

	repne scasb ;scan string by byte while not repeating
	not rcx
	dec rcx
	mov rax, rcx
	ret
 
