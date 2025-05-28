#include <stdlib.h>

size_t cantidad_letras(char *palabra)
{
	size_t contador = 0;
	while (palabra[contador] != '\0')
	{
		contador++;
	}
	return contador;
}

void pasar_a_mayusculas(char *palabra)
{
	size_t diferencia = 'A' - 'a';
	size_t cant_letras = cantidad_letras(palabra);
	for (size_t i = 0; i < cant_letras; i++)
	{
		if (palabra[i] >= 'a' && palabra[i] <= 'z')
		{
			palabra[i] += diferencia;
		}
	}
}