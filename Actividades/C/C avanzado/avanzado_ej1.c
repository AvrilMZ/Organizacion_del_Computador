#include <stdio.h>
#include <string.h>

#define MAX_MONSTRUOS 5
#define MAX_NOMBRE 20

typedef struct monstruo
{
	char nombre[MAX_NOMBRE];
	int vida;
	double ataque;
	double defensa;
} monstruo_t;

void imprimir_monstruo(monstruo_t mons)
{
	printf("Nombre: ");
	for (int i = 0; i < strlen(mons.nombre); i++)
	{
		printf("%c", mons.nombre[i]);
	}
	printf("\nVida: %i\n", mons.vida);
	printf("Ataque: %.2f\n", mons.ataque);
	printf("Defensa: %.2f\n", mons.defensa);
}

int main()
{
	monstruo_t monstruos[MAX_MONSTRUOS];
	int tope = 0;

	strcpy(monstruos[0].nombre, "pepe");
	monstruos[0].vida = 10;
	monstruos[0].ataque = 20;
	monstruos[0].defensa = 15;
	tope++;

	imprimir_monstruo(monstruos[0]);

	return 0;
}