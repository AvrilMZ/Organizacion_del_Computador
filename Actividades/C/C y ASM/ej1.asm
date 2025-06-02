global cesarCod

section .text
	extern calloc
	extern strlen

cesarCod:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = palabra
	mov r13d, esi ; r13 = x

	call strlen
	mov r14, rax ; r14 = largo

	inc rax
	mov rdi, rax
	mov rsi, 1
	call calloc
	mov r15, rax ; r15 = resultado

	xor r9, r9 ; r9 = i = 0

	.for:
		cmp r9, r14 ; i == largo
		jge .fin

		mov r10b, BYTE [r12 + r9] ; r10b = palabra[i]
		add r10b, r13b ; r10b += x
		mov BYTE [r15 + r9], r10b ; resultado[i] = palabra[i] + x
		inc r9 ; i++
		jmp .for

	.fin: 
		mov BYTE [r15 + r14], 0 ; resultado[largo] = '\0'
		mov rax, r15

		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret