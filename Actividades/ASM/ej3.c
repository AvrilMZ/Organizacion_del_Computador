#include <string.h>

int countChars(char *s, char c)
{
	int contador = 0;
	size_t cantidad_letras = strlen(s);
	for (size_t i = 0; i < cantidad_letras; i++)
	{
		if (s[i] == c)
		{
			contador++;
		}
	}
	return contador;
}