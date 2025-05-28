#include <stdio.h>
#include <stdint.h>

int main()
{
	uint8_t *x = (uint8_t *)0xF0;
	int8_t *y = (int8_t *)0xF6;

	printf("Dir de x: %p Valor: %d\n", (void *)x, *x);
	printf("Dir de y: %p Valor: %d\n", (void *)y, *y);

	// Devolver ́a:
	//  Dir de x: 0xF0 Valor: 255
	//  Dir de y: 0xF6 Valor: -128
}

/**
 * x es un unsigned de 1 byte mientras que y es un signed integer de 1 byte.
 * El tipo unsigned es un entero sin signo, por lo que sus valores van de 0 a 255 (son >= 0).
 * El tipo signed integer usa complemento a dos para representar números negativos:
 * 	Complemento a dos:
 * 		- Se toman los bits que representan a ese número positivamente;
 * 		- Se invierten todos los bits;
 * 		- Se suma 1.
 * 	Si el bit más significativo es cero es positivo, si es uno es negativo.
 * 	En un rango de 4 bits sus valores van del -8 al 7.
 * 	En un rango de 8 bits (como acá) van del -128 al 127.
 */