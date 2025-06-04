extern calloc

seccion .text:

map:
	push rbp
	mov rbp, rsp
	
	push rbx
	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = array
	mov r13, rsi ; r13 = func

	mov rdi, 1
	mov rsi, 16 ; rsi = sizeof(array_t)
	call calloc
	mov r14, rax ; r14 = nuevo

	mov r8d, DWORD [r12]
	mov DWORD [r14], r8d ; nuevo->type = array->type
	mov r9b, BYTE [r12 + 4]
	mov BYTE [r14 + 4], r9b ; nuevo->size = array->size;
	mov r10b, BYTE [r12 + 5]
	mov BYTE [r14 + 5], r10b ; nuevo->capacity = array->capacity

	xor rdi, rdi
	mov dil, BYTE [r12 + 4]
	mov rsi, 8 ; rsi = sizeof(void *)
	call calloc
	mov r15, rax ; r15 = nuevo->data
	mov QWORD [r14 + 8], r15

	xor rbx, rbx ; rbx = i = 0

	.for:
		cmp bl, BYTE [r12 + 4] ; i < array->size
		jge .fin

		mov rdi, QWORD [r12 + 8] ; rdi = array->data
        	mov rdi, QWORD [rdi + rbx * 8] ; rdi = array->data[i]
		call r13
		mov rdi, QWORD [r14 + 8] ; rdi = nuevo->data
        	mov QWORD [rdi + rbx * 8], rax ; nuevo->data[i] = func(array->data[i])

		inc bl
		jmp .for

	.fin:
		mov rax, r14

		pop r15
		pop r14
		pop r13
		pop r12
		pop rbx

		pop rbp
		ret