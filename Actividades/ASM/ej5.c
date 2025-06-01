void diagonal(short *matriz, short n, short *vector)
{
	for (int i = 0; i < n; i++)
	{
		vector[i] = matriz[i * n + i];
	}
}