#include <stdlib.h>
#include <stdio.h>

#define CANT_LADOS 6
const int VECES = 60000000;

int main()
{
	int sumador[CANT_LADOS] = {0};
	for (int i = 0; i < VECES; i++)
	{
		int resultado = rand() % CANT_LADOS + 1;
		sumador[resultado - 1]++;
	}

	for (int i = 0; i < CANT_LADOS; i++)
	{
		printf("Salió %i veces el número %i\n", sumador[i], i + 1);
	}

	return 0;
}