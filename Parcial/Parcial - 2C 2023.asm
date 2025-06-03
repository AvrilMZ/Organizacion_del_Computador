seccion .text
	extern calloc

sumaElemento:
	push rbp
	mov rbp, rsp

	push rbx
	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = lista
	mov r13, rsi ; r13 = index
	mov r14, rdx ; r14 = new

	mov rdi, 1
	mov rsi, 16 ; sizeof(listElem_t)
	call calloc
	mov r15, rax ; r15 = nuevo
	mov BYTE [r15], r14b ; nuevo->c = new

	mov rbx, QWORD [r12 + 8] ; listElem_t *nodo = lista->first
	xor r8, r8 ; r8 = i = 0

	.for:
		cmp r8d, DWORD [r12] ; i < lista->size
		jge .fin

		cmp BYTE [rbx], r13b ; nodo->c == index
		je .iguales

		mov rbx, QWORD [rbx + 8] ; nodo = nodo->next
		inc r8
		jmp .for

	.iguales
		mov r9, QWORD [rbx + 8] ; r9 = nodo->next
		mov QWORD [r15 + 8], r9 ; nuevo->next = nodo->next
		mov QWORD [rbx + 8], r15 ; nodo->next = nuevo

		mov r10, DWORD [r12]
		sub r10, 1
		cmp r8, r10 ; i == lista->size - 1
		je .ultimo

		add DWORD [r12], 1 ; lista->size++
		jmp .fin

	.ultimo
		mov DWORD [r12 + 16], r15 ; lista->last = nuevo
		add DWORD [r12], 1 ; lista->size++
		jmp .fin

	.fin:
		pop r15
		pop r14
		pop r13
		pop r12
		pop rbx

		pop rbp
		ret