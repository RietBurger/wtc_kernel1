global _ft_isalpha

section .text
_ft_isalpha:
	cmp		rdi, 'A'
	jnge	exit
	cmp		rdi, 'Z'
	jle		caps
	jnle	smalls

caps:
	mov		rax, 1
	ret

smalls:
	cmp		rdi, 'a'
	jnge	exit
	cmp		rdi, 'z'
	jnle	exit
	mov		rax, 1
	ret

	
exit:
	mov		rax, 0
	ret
	
