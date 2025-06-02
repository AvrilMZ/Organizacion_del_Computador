%define SIZE_C 10
%define INT_SIZE 4

section .text
	global primerMaximo

primerMaximo:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15
	push rbx

	mov r12, rdi; r12 = matriz
	mov r13, rsi ; r13 = f
	mov r14, rdx ; r14 = c

	mov DWORD [r13], 0 ; *f = 0
   	mov DWORD [r14], 0 ; *c = 0

	mov r15, r12 ; r15 = &matriz[0][0]
	mov ebx, DWORD [r15] ; rbx = matriz[0][0]

	xor r8, r8 ; r8 = i = 0

	.for_fila
		cmp r8, SIZE_C ; i == SIZE_C
		jge .fin

		xor r9, r9 ; r9 = j = 0

	.for_col
		cmp r9, SIZE_C ; j == SIZE_C
		jge .sig_fila

		mov eax, r8d ; rax = i
		imul eax, SIZE_C ; i * SIZE_C
		add eax, r9d ; i * SIZE_C + j
		imul eax, INT_SIZE ; (i * SIZE_C + j) * 4 = offset
		
		mov edx, DWORD [r12 + rax] ; rdx = matriz[i][j]

		cmp edx, ebx ; matriz[i][j] == *puntero_max
		jle .sig_col

		mov ebx, edx ; puntero_max = &matriz[i][j]
		mov r15, r12 ; *puntero_max = matriz[i][j]
    		add r15, rax ; puntero_max + ((i * SIZE_C + j) * 4)

		mov DWORD [r13], r8d ; *f = i
		mov DWORD [r14], r9d ; *c = j

		jmp .sig_col

	.sig_fila
		inc r8 ; i++
		jmp .for_fila

	.sig_col
		inc r9 ; j++
		jmp .for_col

	.fin
		mov rax, r15

		pop rbx
		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret