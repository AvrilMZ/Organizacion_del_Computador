#include <stdint.h>

#define VIDEO_COLS 80
#define VIDEO_FILS 50

// Cada posicion de memoria tiene 2 bytes
typedef struct ca_s
{
	uint8_t c; // caracter
	uint8_t a; // atributos
} ca;

void screen_draw_layout(void)
{
	// VIDEO es un puntero a la dirección de memoria del buffer de video
	ca(*p)[VIDEO_COLS] = (ca(*)[VIDEO_COLS])VIDEO;
	uint32_t f, c;
	for (f = 0; f < VIDEO_FILS; f++)
	{
		for (c = 0; c < VIDEO_COLS; c++)
		{
			p[f][c].c = ' ';
			p[f][c].a = 0x10;
		}
	}
}

/**
 * ¿Qué hace `ca(*p)[VIDEO COLS] = (ca(*)[VIDEO COLS])VIDEO;`?
 *	- declara p como un puntero a un array de VIDEO_COLS elementos de tipo ca.
 * 	- convierte la dirección VIDEO a un puntero del mismo tipo que p.
 * Está configurando p para que apunte al buffer de video y lo trate como una matriz
 * bidimensional de estructuras ca con dimensiones VIDEO_FILS * VIDEO_COLS.
 *
 * ¿Por qué funciona esto: `p[f][c].c = ’ ’;`?
 * 	- Accede a la fila f del buffer de video. Como p es un puntero a arrays de
 * 	VIDEO_COLS elementos, p[f] representa toda una fila;
 * 	- Accede al elemento en la columna c de la fila f. Esto nos da una
 * 	estructura ca específica;
 * 	- Accede al campo c (carácter) de esa estructura ca.
 * Funciona porque el compilador calcula automáticamente las direcciones:
 * 	- Para p[f][c], calcula: `base + (f * VIDEO_COLS + c) * sizeof(ca)`;
 * 	- Esto permite acceder al buffer de video lineal como si fuera una matriz 2D.
 */