section .data
	IGUALES	dd 0
	MENOR dd 1
	MAYOR dd -1
	NULL db "NULL"

section .text
	global strLen
	global strCmp
	global strPrint
	extern fwrite

strLen:
	push ebp ; guardo el valor actual de ebp en la pila
	mov ebp, esp ; ebp apunta al "inicio" de la pila

	mov esi, [ebp + 8] ; puntero 'a'
	xor eax, eax ; contador

	.while:
		mov dl, [esi + eax] ; agarro el caracter (dl = 1 byte = 1 char)
		cmp dl, 0
		je .fin
		inc eax
		jne .while

	ret

	.fin:
		pop ebp ; vuelve al valor anterior de ebp de la pila
		ret

strCmp:
	push ebp
	mov ebp, esp

	mov esi, [ebp + 8] ; puntero 'a'
	mov edi, [ebp + 12] ; puntero 'b'

	.while:
		mov al, [esi] ; leo siguiente caracter
		mov bl, [edi]

		cmp al, bl
		jne .diff ; si son distintos, comparo cuál es mayor

		cmp al, 0 ; si llego a acá sabemos que al = bl
		je .iguales ; si ambos son '\0' => strings iguales

		inc esi
		inc edi
		jmp .while
	
	.diff:
		cmp al, bl
		jl .menor
		jg .mayor

	.iguales:
		mov eax, [IGUALES]
		jmp .fin

	.menor:
		mov eax, [MENOR]
		jmp .fin

	.mayor:
		mov eax, [MAYOR]
		jmp .fin

	.fin:
		pop ebp
		ret

strPrint:
	; ¿?