#define SIZE_C 10

int *primerMaximo(int (*matriz)[SIZE_C], int *f, int *c)
{
	int *puntero_max = &matriz[0][0];
	*f = 0;
	*c = 0;

	for (int i = 0; i < SIZE_C; i++)
	{
		for (int j = 0; j < SIZE_C; j++)
		{
			if (matriz[i][j] > *puntero_max)
			{
				puntero_max = &matriz[i][j];
				*f = i;
				*c = j;
			}
		}
	}

	return puntero_max;
}