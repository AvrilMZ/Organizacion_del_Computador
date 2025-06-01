seccion .text:
	global countChars
	extern strlen

countChars:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r13, rsi ; r13 = c
	xor r14, r14 ; contador = 0

	call strlen
	mov r15, rax ; r15 = cantidad_letras
	mov r12, rdi ; r12 = *s

	.for:
		cmp r14, r15 ; contador == cantidad_letras
		jge .fin

		cmp BYTE [r12], r13b ; *s == c
		je .incrementar_contador

		inc r12 ; siguiente caracter
		jmp .for

	.incrementar_contador
		inc r14 ; contador++
		inc r12 ; siguiente caracter
		jmp .for

	.fin:
		mov rax, r14 ; return contador

		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret