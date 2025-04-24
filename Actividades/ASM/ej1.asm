; Sumo todos los elementos de un arreglo de 16 enteros de 32 bits (Cada posición tiene un 1 para facilidad)

section .data
	VECTOR times 16 dd 1 ; Se utiliza dd ya que cada entero ocupa 4 bytes
	TEXTO db "La suma de los elementos es %i", 10, 0

section .text
	global main
	extern printf

sumar_elementos_vector:
	xor eax, eax ; sumador
	xor esi, esi ; contador de elementos
	
	.for:
		add eax, [VECTOR + esi] ; sumo el valor
		add esi, 4 ; paso al siguiente elemento
		cmp esi, 64 ; chequeo si llego a los 16 elementos: (4 * 16)
		jne .for
	
	ret

main:
	mov edi, VECTOR ; cargar la dirección de memoria de VECTOR en edi
	call sumar_elementos_vector
	
	mov edi, TEXTO ; primer argumento de printf
	mov esi, eax ; paso el resultado a esi (segundo argumento de printf)
	xor eax, eax ; limpiar eax para printf (número de argumentos flotantes)
	call printf

	xor eax, eax ; return 0
	ret

section .note.GNU-stack noalloc noexec nowrite progbits