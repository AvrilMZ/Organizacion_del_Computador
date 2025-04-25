#include <stdint.h>
#include <stdio.h>

const int IGUALES = 0;
const int MENOR = 1;
const int MAYOR = -1;
const char* TEXTO_NULL = "NULL";

/**
 * Retorna la cantidad de caracteres distintos de cero del string pasado por parámetro.
 */
uint32_t strLen(char* a) 
{
	uint32_t contador = 0;
	while (*a != '\0') {
		contador++;
		a++;
	}
	return contador;
}

/**
 * Compara dos strings en orden lexicográfico.
 * Devuelve:
 * 	- 0 si son iguales
 * 	- 1 si a < b
 * 	- -1 si a > b
 */
int32_t strCmp(char* a, char* b) 
{
	while (*a == *b && (*a || *b) != '\0') {
		a++;
		b++;
	}
	
	if (*a == *b) {
		return IGUALES;
	} else if (*a < *b) {
		return MENOR;
	}
	return MAYOR;
}

/**
 * Escribe el string en el stream indicado a través de 'pFile'. Si el string es vacío escribe NULL.
 */
void strPrint(char* a, FILE* pFile) 
{
	if (!a || a[0] == '\0') {
		fwrite(TEXTO_NULL, sizeof(char), 4, pFile);
	}
	fwrite(a, sizeof(char), strLen(a), pFile);
}