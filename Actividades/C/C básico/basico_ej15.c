int factorial(int num)
{
	if (num < 0)
	{
		return -1;
	}

	if (num == 1 || num == 0)
	{
		return 1;
	}

	return num * factorial(num - 1);
}

int main()
{
	return 0;
}