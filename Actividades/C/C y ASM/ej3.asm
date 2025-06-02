section .text:
	extern rand

longitud:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = cliente t[]
	mov r13, rsi ; r13 = longitud

	call rand
	xor rdx, rdx
	div r13 ; rax = rand() / longitud, rdx = rand() % longitud
	mov r14, rdx ; r14 = i

	mov rax, r14 ; rax = i
	mov rcx, 64 ; rcx = sizeof(cliente_t)
	mul rcx ; rax = índice * sizeof(cliente_t)
	add rax, r12 ; rax = &cliente_t[i]

	pop r15
	pop r14
	pop r13
	pop r12

	pop rbp
	ret