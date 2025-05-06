#include <stdio.h>

int main()
{
	float f_valor = 0.1;
	double d_valor = 0.1;
	printf("Valor como float: %e\n", f_valor);
	printf("Valor como double: %e\n", d_valor);
	printf("Valor float casteado a int: %i\n", (int)f_valor);
	printf("Valor double casteado a int: %i\n", (int)d_valor);

	return 0;
}

/*
 * Float tiene menos precisión que double.
 * Luego del casteo podemos ver que:
 * 	- Se trunca toda la parte decimal.
 * 	- No se redondea, se elimina directamente toda la parte decimal.
 */