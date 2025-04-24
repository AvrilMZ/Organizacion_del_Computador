#include <stdint.h>
#include <stdio.h>

const int MAXIMO = 16;

/**
 * Se asume que el tope de 'vector' es igual a su máximo.
 * Devuelve la suma de todos los elementos de 'vector'.
 */ 
int32_t sumar_elementos_vector(int32_t vector[MAXIMO])
{
	int32_t suma = 0;
	for (int32_t i = 0; i < MAXIMO; i++) {
		suma += vector[i];
	}
	return suma;
}

int main() {
	int32_t vector[MAXIMO];
	for (int32_t i = 0; i < MAXIMO; i++) {
		vector[i] = 1;
	}
	printf("La suma de los elementos es %i\n", sumar_elementos_vector(vector));

	return 0;
}