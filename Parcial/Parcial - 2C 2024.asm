global stringify
extern fprintf

section .data
	ENTERO db "%i", 0
	SIGUIENTE db " -> ", 0
	ULTIMO db "NULL", 10, 0

section .text

stringify:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = fp
	mov r13, rsi ; r13 = list

	cmp DWORD [r13 + 16], 0
	je .fin

	mov r14, QWORD [r13] ; r14 = nodo
	xor r15, r15 ; r15 = i = 0

	.for:
		cmp r15d, DWORD [r13 + 16] ; i < list->size
		jge .fin

		mov rdi, r12
		mov rsi, ENTERO
		mov rdx, DWORD [r14 + 8]
		call fprintf ; fprintf(fp, "%i", nodo->data)

		mov r8, DWORD [r13 + 16]
		sub r8, 1
		cmp r15, r8 ; i == list->size - 1
		je .ultimo

		mov rdi, r12
		mov rsi, SIGUIENTE
		call fprintf ; fprintf(fp, SIGUIENTE)

		mov r14, QWORD [r14] ; nodo = nodo->next
		inc r15
		jmp .for

	.ultimo
		mov rdi, r12
		mov rsi, SIGUIENTE
		call fprintf ; fprintf(fp, SIGUIENTE)
		jmp .fin

	.fin:
		mov rdi, r12
		mov rsi, ULTIMO
		call fprintf ; fprintf(fp, ULTIMO)

		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret