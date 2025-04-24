; Sumo todos los elementos de un arreglo de 16 enteros de 32 bits (Cada posición tiene un 1 para facilidad)

section .data
	vector times 16 dd 1 ; Se utiliza dd ya que cada entero ocupa 4 bytes
	TEXTO: db "La suma de los elementos es %i", 10, 0

section .text
	global main
	extern printf
	
main:
	call sumar_elementos_vector
	mov rdi, TEXTO         ; primer argumento de printf
	mov esi, eax           ; paso el resultado a esi (segundo argumento de printf)
	xor eax, eax           ; limpiar rax para printf (número de argumentos flotantes)
	call printf

	xor eax, eax           ; return 0
	ret
sumar_elementos_vector:
	mov eax, 0 ; Sumador
	mov esi, 0 ; Contador de elementos
	
	.for:
		add eax, [vector + esi] ; Sumo el valor
		add esi, 4 ; Paso al siguiente elemento
		cmp esi, 64 ; Chequeo si llego a los 16 elementos: (4 * 16)
		jne .for
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
