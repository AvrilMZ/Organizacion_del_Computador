#include <stdio.h>

#define MAX_ELEMENTOS 5

int main()
{
	int arreglo[MAX_ELEMENTOS] = {1, 2, 3, 4, 5};
	int tope_arreglo = 5;
	int modificado[MAX_ELEMENTOS];
	int tope_modificado = 0;

	int size_rotacion = 2;
	for (int i = size_rotacion; i < tope_arreglo; i++)
	{
		modificado[i - size_rotacion] = arreglo[i];
		tope_modificado++;
	}

	for (int i = 0; i < size_rotacion; i++)
	{
		modificado[tope_modificado] = arreglo[i];
		tope_modificado++;
	}

	for (int i = 0; i < tope_modificado; i++)
	{
		printf("%i\n", modificado[i]);
	}

	return 0;
}