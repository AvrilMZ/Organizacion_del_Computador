#include <stdio.h>
#define FELIZ 0
#define TRISTE 1

void ser_feliz(int estado);
void print_estado(int estado);

int main()
{
	int estado = TRISTE;
	ser_feliz(estado);
	print_estado(estado);
}

void ser_feliz(int estado)
{
	estado = FELIZ;
}

void print_estado(int estado)
{
	printf("Estoy %s\n", estado == FELIZ ? "feliz" : "triste");
}

/**
 * Imprime "Estoy triste" ya que con la función 'ser_feliz' se modifica el valor local del ámbito.
 */