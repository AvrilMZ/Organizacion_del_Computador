#include <stdio.h>

int main()
{
	int matrix[3][4] = {
	    {1, 2, 3, 4},
	    {5, 6, 7, 8},
	    {9, 10, 11, 12}};
	// p apunta al int en la fila 0, columna 0
	int *p = &matrix[0][0];

	// ¿qué es reshape?
	int (*reshape)[2] = (int (*)[2])p;

	printf("%d\n", p[3]);	       // Qué imprime esta línea?
	printf("%d\n", reshape[1][1]); // Qué imprime esta línea?

	return 0;
}

/**
 * reshape es un puntero a un array de 2 enteros.
 * Hace un cast del puntero p (que apunta al primer elemento de la matriz)
 * para reinterpretarlo como un puntero que apunta a arrays de 2 elementos.
 * Esto cambia la vista de la matriz original de 3x4 a una matriz de 6x2.
 *
 * Línea `printf("%d\n", p[3]);` imprime 4 ya que accede a la 4ta posicion de p original.
 *
 * Línea `printf("%d\n", reshape[1][1]);` imprime 4 ya que reshape[1] apunta al segundo
 * array de 2 elementos (elementos 3 y 4 de la matriz original), y reshape[1][1] accede
 * al segundo elemento de ese array, que es 4.
 *
 * reshape[0]: [1, 2]
 * reshape[1]: [3, 4]
 * reshape[2]: [5, 6]
 * reshape[3]: [7, 8]
 * reshape[4]: [9, 10]
 * reshape[5]: [11, 12]
 */