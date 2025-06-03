global agregarAdelante_asm
global valorEn
global destruirLista

seccion .text
	extern calloc

agregarAdelante_asm:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14

	mov r12d, edi ; r12d = valor
	mov r13, rsi ; r13 = siguiente

	mov rdi, 1
	mov rsi, 16 ; rsi = sizeof(node_t)
	call calloc
	mov r14, rax ; r14 = adelante

	mov QWORD [r14], r13 ; adelante->siguiente = siguiente
	mov DWORD [r14 + 8], r12d ; adelante->valor = valor

	mov rax, r14

	pop r14
	pop r13
	pop r12

	pop rbp
	ret