#include <stdio.h>

int main()
{
	int x = 42;
	int *p = &x;
	printf("Direccion de x: %p Valor: %d\n", (void *)&x, x);
	printf("Direccion de p: %p Valor: %p\n", (void *)&p, (void *)p);
	printf("Valor de lo que apunta p: %d\n", *p);
}

/**
 * p contiene la direccion memoria de x, por lo que apunta a su valor.
 * x es el valor y &x la direccion de memoria donde se almacena ese valor.
 * p es la direccion de memoria a la que apunta, mientras que *p es el valor apuntado.
 *
 * Se va a imprimir:
 * 	- Direccion de x: 0x... Valor: 42
 * 	- Direccion de p: (direccion de memoria de x) Valor: (direccion de memoria de x)
 * 	- Valor de lo que apunta p: 42
 */