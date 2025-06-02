#include <string.h>

char *prefijo_de(char *palabra1, char *palabra2)
{
	size_t largo1 = strlen(palabra1);
	size_t largo2 = strlen(palabra2);
	size_t largo_minimo;
	if (largo1 <= largo2)
	{
		largo_minimo = largo1;
	}
	else
	{
		largo_minimo = largo2;
	}

	int tamaño_prefijo = 0;
	int distinto = 0;
	for (size_t i = 0; i < largo_minimo && distinto == 0; i++)
	{
		if (palabra1[i] == palabra2[i])
		{
			tamaño_prefijo++;
		}
		else
		{
			distinto = 1;
		}
	}

	char *prefijo = calloc(tamaño_prefijo + 1, sizeof(char));
	if (!prefijo)
	{
		return NULL;
	}

	for (int i = 0; i < tamaño_prefijo; i++)
	{
		prefijo[i] = palabra1[i];
	}
	prefijo[tamaño_prefijo] = '\0';

	return prefijo;
}