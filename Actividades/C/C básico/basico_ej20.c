int b, c;

void f(void)
{
	int b, d;
}

void g(int a)
{
	int c;
	{
		int a, d;
	}
}

/**
 * Las únicas variables que perduran por fuera de las funciones son 'b' y 'c' ya que son globales.
 * En la función 'g', 'c' no podra tomar el valor ni interactuar con 'a' o 'd' ya que estan en otro sub-ámbito.
 * Ninguna función modifica los valores de 'b' y 'c' ya que no tienen un puntero a las direcciones de las mismas.
 */