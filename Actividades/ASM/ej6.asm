section .text
	global gris

gris:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = matriz
	mov r13, rsi ; r13 = n
	mov r14, rdx ; r14 = resultado

	xor r8, r8 ; r8 = fila = 0
	
	.for_fila:
		cmp r8, r13 ; fila == n
		jge .fin

		xor r9, r9 ; r9 = col = 0

	.for_col:
		cmp r9, r13 ; col == n
		jge .sig_fila

		mov r10, r8 ; r10 = fila
		imul r10, r13 ; fila * n
		add r10, r9 ; (fila * n) + col

		mov rax, r10 ; rax = (fila * n) + col
		imul rax, 3 ; rax = ((fila * n) + col) * 3 = offset de matriz

		mov dl, byte [r12 + rax] ; rdx = R
		mov bl, byte [r12 + rax + 1] ; rbx = G
		mov cl, byte [r12 + rax + 2] ; rcx = B

		mov al, bl ; rax = G
		shl al, 1 ; G * 2
		add dl, al ; R += 2 * G
		add dl, cl ; (R + 2 * G) += B
		shr dl, 2 ; rdx = (R + 2 * G + B) / 4

		mov [r14 + r10], dl ; resultado[fila * n + col] = gris

		inc r9 ; col++
		jmp .for_col

	.sig_fila
		inc r8 ; fil++
		jmp .for_fila

	.fin:
		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret