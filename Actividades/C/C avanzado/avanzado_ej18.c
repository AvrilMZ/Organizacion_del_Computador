#include <stdio.h>

void allocateArray(int *arr, int size, int value)
{
	arr = (int *)malloc(size * sizeof(int));
	if (arr != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = value;
		}
	}
}

int main()
{
	int *vector = NULL;
	allocateArray(vector, 5, 45);
	for (int i = 0; i < 5; i++)
		printf("%d\n", vector[i]);
	free(vector);
}

/**
 * `allocateArray` solo modifica el puntero dentro de su ambito,
 * por lo que la reserva de memoria no tiene efecto por fuera de la funcion.
 *
 * Cuando se llama la funcion en el main, la variable vector sigue siendo
 * NULL luego del procesamiento.
 *
 * Resultaria en una perdida de memoria ya que el malloc dentro de
 * `allocateArray` no puede ser liberado nunca.
 */