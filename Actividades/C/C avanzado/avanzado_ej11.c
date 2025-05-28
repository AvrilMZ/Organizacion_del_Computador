#include <stdio.h>

uint16_t *secuencia(uint16_t n)
{
	uint16_t arr[n];
	for (uint16_t i = 0; i < n; i++)
		arr[i] = i;
	return arr;
}

int main()
{
	uint16_t *arr = secuencia(10);
	printf("%d\n", arr[0]);
	return 0;
}

/**
 * Falta incluir la libreria <stdint.h>.
 * La funcion `secuencia` intenta devolver un puntero a un arreglo local lo cual es un error.
 * Luego en main se intenta acceder a un campo de ese arreglo invalido lo cual generaria un
 * segmentation fault, ya que estaria intentando acceder a una direccion de memoria que no me
 * corresponde.
 */