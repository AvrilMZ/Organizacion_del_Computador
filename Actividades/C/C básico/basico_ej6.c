#include <stdio.h>

int main()
{
	int mensaje_secreto[] = {116, 104, 101, 32, 103, 105, 102, 116, 32, 111,
				 102, 32, 119, 111, 114, 100, 115, 32, 105, 115, 32, 116, 104, 101, 32,
				 103, 105, 102, 116, 32, 111, 102, 32, 100, 101, 99, 101, 112, 116, 105,
				 111, 110, 32, 97, 110, 100, 32, 105, 108, 108, 117, 115, 105, 111, 110};

	size_t length = sizeof(mensaje_secreto) / sizeof(int);
	char decoded[length];

	for (size_t i = 0; i < length; i++)
	{
		decoded[i] = (char)(mensaje_secreto[i]); // casting de int a char
	}

	for (size_t i = 0; i < length; i++)
	{
		if (i == length - 1)
		{
			printf("%c\n", decoded[i]);
		}
		else
		{
			printf("%c", decoded[i]);
		}
	}
}

/**
 * Se imprime "the gift of words is the gift of deception and illusion".
 * Se calcula usando sizeof(mensaje_secreto) / sizeof(int) porque:
 * 	- sizeof(mensaje_secreto) devuelve el tamaño total en bytes del array
 * 	- sizeof(int) devuelve el tamaño en bytes de un entero
 * 	- La división da como resultado el número de elementos del array
 * No pasaria nada si se modifica el tamaño ya que funcionaría correctamente para cualquier tamaño.
 * Se usa size_t porque es el tipo de retorno de sizeof.
 */