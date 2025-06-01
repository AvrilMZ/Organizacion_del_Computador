#include <string.h>

int countChars(char *s, char c)
{
	int contador = 0;
	int cantidad_letras = strlen(s);
	for (int i = 0; i < cantidad_letras; i++)
	{
		if (s[i] == c)
		{
			contador++;
		}
	}
	return contador;
}