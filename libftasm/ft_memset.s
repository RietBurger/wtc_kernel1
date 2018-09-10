global _ft_memset

section .text
_ft_memset:

;void *ft_memset(void *b, int c, size_t len)
	;rdi/ b - is str and return
	;rsi/ c - is character to fill with
	;rdx/ len - is length
	
	mov rcx, rdx
	mov	rax, rsi
	rep		stosb

	ret


