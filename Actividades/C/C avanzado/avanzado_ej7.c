void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	int x = 10, y = 20;
	swap(&x, &y);
	printf("x: %d, y: %d\n", x, y);
}

/**
 * Si la firma de la funcion swap fuera `void swap(int a, int b)` el intercambio de valores
 * moriria dentro del ambito de la funcion y no se guardarian los nuevos valores, para realizarlo
 * necesitamos un puntero a la direccion de memoria donde se almacenan esos datos y cambiarlos
 * desde ahi.
 */