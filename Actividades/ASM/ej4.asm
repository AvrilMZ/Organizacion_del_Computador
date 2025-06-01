section .text
	global intercambiar
	extern strlen

intercambiar:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	call strlen
	mov r13, rax ; r13 = largo
	mov r12, rdi ; r12 = s
	xor r14, r14 ; r14 = i = 0
	mov r15, r13
	shr r15, 1 ; r15 = largo / 2

	.for:
		cmp r14, r15 ; i == largo / 2
		jge .fin

		mov r8b, BYTE [r12 + r14] ; r8 = letra
		mov al, [r12 + r13 - 1 - r14] ; al = s[largo - 1 - i]
		mov [r12 + r14], al ; s[i] = s[largo - 1 - i]
		mov BYTE [r12 + r13 - 1 - r14], r8b ; s[largo - 1 - i] = letra
		
		inc r14
		jmp .for

	.fin:
		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret