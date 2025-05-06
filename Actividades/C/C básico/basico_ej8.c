#include <stdio.h>

int main()
{
	int i = 1;
	printf("Resultado de i++: %i\n", i++);
	printf("Resultado de ++i: %i\n", ++i);
	return 0;
}

/**
 * i++ (Post-incremento):
 * 	- Primero devuelve el valor actual de la variable
 * 	- Después incrementa el valor de la variable en 1
 * 	- En una expresión, el valor usado es el valor original antes del incremento
 *
 * ++i (Pre-incremento):
 * 	- Primero incrementa el valor de la variable en 1
 * 	- Después devuelve el nuevo valor incrementado
 * 	- En una expresión, el valor usado es el valor ya incrementado
 */