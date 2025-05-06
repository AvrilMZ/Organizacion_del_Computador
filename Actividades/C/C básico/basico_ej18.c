#include <stdio.h>

#define FELIZ 0
#define TRISTE 1

int estado = TRISTE;
void alcoholizar();
void print_estado();

int main()
{
	print_estado();
	alcoholizar();
	print_estado();
	alcoholizar();
	alcoholizar();
	alcoholizar();
	print_estado();
}

void alcoholizar()
{
	static int cantidad = 0;
	cantidad++;
	if (cantidad < 3)
	{
		estado = FELIZ;
	}
	else
	{
		estado = TRISTE;
	}
}

void print_estado()
{
	printf("Estoy %s\n", estado == FELIZ ? "feliz" : "triste");
}

/**
 * Con static:
 * 	- El programa imprime: "Estoy triste", "Estoy feliz", "Estoy triste"
 * 	- La variable cantidad mantiene su valor entre llamadas a alcoholizar()
 * 	- Después de 3 llamadas, cantidad supera el valor 2 y el estado vuelve a TRISTE
 * Sin static:
 * 	- El programa imprime: "Estoy triste", "Estoy feliz", "Estoy feliz"
 * 	- La variable cantidad se reinicia a 0 en cada llamada a alcoholizar()
 * 	- En cada llamada, cantidad siempre vale 1 después del incremento
 * 	- Como siempre es menor que 3, el estado nunca vuelve a TRISTE
 *
 * Static permite que la variable conserve su valor entre distintas llamadas a la función.
 */