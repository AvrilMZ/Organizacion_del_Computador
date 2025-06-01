section .text
	global diagonal

diagonal:
	push rbp
	mov rbp, rsp

	push r12
	push r13

	mov r12, rdi ; r12 = matriz
	mov r13w, si ; r13 = n
	mov r14, rdx ; r14 = vector

	xor rcx, rcx ; rcx = i = 0

	.for:
		mov r10, rcx
		imul r10, r13 ; r10 = i * n
		add r10, rcx ; r10 = i * n + i
		shl r10, 1 ; * sizeof(short)

		mov r11, rcx
		shl r11, 1 ; offset en vector

		mov r8w, [r12 + r10] ; r8w = matriz[i * n + i]
		mov [r14 + r11], r8w ; vector[i] = r8w

		inc rcx
		cmp rcx, r13
		jne .for

	.fin:
		pop r13
		pop r12
		pop rbp
		ret