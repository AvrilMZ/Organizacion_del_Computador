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

monstruo_t evolucion(monstruo_t monstruo)
{
	monstruo.ataque += 10;
	monstruo.defensa += 10;
	return monstruo;
}

void imprimir_mounstruo(monstruo_t mons)
{
	printf("Nombre: ");
	for (int i = 0; i < strlen(mons.nombre); i++)
	{
		printf("%c", mons.nombre[i]);
	}
	printf("\nVida: %i\n", mons.vida);
	printf("Ataque: %e\n", mons.ataque);
	printf("Defensa: %e\n", mons.defensa);
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

	printf("ANTES DE EVOLUCIONAR:\n");
	imprimir_mounstruo(monstruos[0]);

	monstruos[0] = evolucion(monstruos[0]);

	printf("\nDESPUES DE EVOLUCIONAR:\n");
	imprimir_mounstruo(monstruos[0]);

	return 0;
}