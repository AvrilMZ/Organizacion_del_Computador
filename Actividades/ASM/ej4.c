#include <string.h>

void intercambiar(char *s)
{
	size_t largo = strlen(s);
	for (size_t i = 0; i < largo / 2; i++)
	{
		char letra = s[i];
		s[i] = s[largo - 1 - i];
		s[largo - 1 - i] = letra;
	}
}