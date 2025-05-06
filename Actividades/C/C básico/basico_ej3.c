#include <stdio.h>

int main()
{
	char c = 100;
	unsigned char uc = 100;
	short s = 30000;
	unsigned short us = 60000;
	int i = 2000000000;
	unsigned u = 4000000000;
	long l = 900000000000;
	unsigned long ul = 100000000000;

	printf("Tamaño char (%c): %zu bytes\n", c, sizeof(c));
	printf("Tamaño unsigned char (%c): %zu bytes\n", uc, sizeof(uc));
	printf("Tamaño short (%i): %zu bytes\n", s, sizeof(s));
	printf("Tamaño unsigned short (%u): %zu bytes\n", us, sizeof(us));
	printf("Tamaño int (%i): %zu bytes\n", i, sizeof(i));
	printf("Tamaño unsigned (%u): %zu bytes\n", u, sizeof(u));
	printf("Tamaño long (%li): %zu bytes\n", l, sizeof(l));
	printf("Tamaño unsigned long (%lu): %zu bytes\n", ul, sizeof(ul));

	return 0;
}