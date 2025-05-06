#include <stdio.h>

int variable_global = 6;

int main()
{
	int variable_local = 5;
	printf("Local: %i\n", variable_local);
	printf("Global: %i\n", variable_global);
	return 0;
}

/*
 * La variable local pisa al valor de la global
 */