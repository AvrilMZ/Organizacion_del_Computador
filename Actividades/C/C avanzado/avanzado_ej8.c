int main()
{
	char *str1 = "Hola";
	char str2[] = "Hola";
	printf("%s\n", str1);
	printf("%s\n", str2);
	return 0;
}

/**
 * El str1 es un puntero a la seccion data la cual no puedo modificar.
 * El str2 es un arreglo creado en el stack que si puedo modificar.
 * Ambos tienen caracter finalizador.
 */