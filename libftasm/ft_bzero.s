
global _ft_bzero

section .text

_ft_bzero:
	test	rsi, rsi ;test whether input is empty
	jz		exit

loop:
	cmp		rsi, 0 ;test whether input is a 0
	je		exit
	mov		BYTE[rdi], 0
	dec		rsi
	inc		rdi
	jmp		loop

exit:
	ret

