#include <string.h>
#include <stdlib.h>

extern char *cesarCod(int arg1, int arg2);

char *cesar(char *palabra, int x)
{
	size_t largo = strlen(palabra);
	char *resultado = calloc(largo + 1, sizeof(char));
	if (!resultado)
	{
		return NULL;
	}

	for (size_t i = 0; i < largo; i++)
	{
		resultado[i] = palabra[i] + x;
	}
	resultado[largo] = '\0';
	return resultado;
}