#include <stdio.h>

#define MAX_ELEMENTOS 5

int main()
{
	int arreglo[MAX_ELEMENTOS] = {1, 2, 3, 4, 5};
	int tope_arreglo = 5;
	int modificado[MAX_ELEMENTOS];
	int tope_modificado = 0;
	for (int i = 1; i < tope_arreglo; i++)
	{
		modificado[i - 1] = arreglo[i];
		tope_modificado++;
		if (i == tope_arreglo - 1)
		{
			modificado[i] = arreglo[0];
			tope_modificado++;
		}
	}

	return 0;
}