;void *ft_memcpy(void *dest, const void *src, size_t n)


global	_ft_memcpy

section .text

_ft_memcpy:
	mov		rcx, rdx
	rep		movsb
	ret
