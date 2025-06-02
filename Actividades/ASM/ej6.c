#include <stdlib.h>
#include <stdint.h>

typedef struct pixel
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} pixel;

void gris(pixel *matriz, short n, uint8_t *resultado)
{
	for (short fila = 0; fila < n; fila++)
	{
		for (short col = 0; col < n; col++)
		{
			pixel p = matriz[fila * n + col];
			uint8_t gris = (p.R + 2 * p.G + p.B) / 4;
			resultado[fila * n + col] = gris;
		}
	}
}