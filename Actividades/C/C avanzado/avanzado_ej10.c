#include <string.h>

/**
 * Devuelve la cantidad de letras que tiene la palabra dada.
 */
size_t cantidad_letras(const char *palabra)
{
	return strlen(palabra);
}

/**
 * Genera una copia de src en cpy.
 */
void copiar_palabra(const char *src, char *cpy)
{
	strcpy(cpy, src);
}

/**
 * Devuelve 1 si son iguales, en caso contrario devuelve 0.
 */
int es_misma_palabra(const char *palabra1, const char *palabra2)
{
	return strcmp(palabra1, palabra2) == 0;
}

/**
 * Concatena palabra2 al final de palabra1 y lo devuelve en el mismo puntero.
 *
 * Se asume que palabra1 tiene espacio suficiente.
 */
void concatenar_palabras(char *palabra1, const char *palabra2)
{
	strcat(palabra1, palabra2);
}

/**
 * `restrict` es un calificador que indica que el puntero es el único medio para
 * acceder a ese objeto dentro de ese ámbito.
 */