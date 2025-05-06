#include <stdio.h>

int g = 10;

void functionA()
{
	int a = 20;
	static int b = 30;
	printf("Dentro de functionA:\n");
	printf(" g = %d\n", g);
	printf(" a = %d\n", a);
	printf(" b = %d\n", b);
	g += 5;
	a += 10;
	b += 5;
}

void functionB()
{
	int a = 40;
	static int c = 50;
	printf("\nDentro de functionB:\n");
	printf(" g = %d\n", g);
	printf(" a = %d\n", a);
	printf(" c = %d\n", c);
	g += 5;
	a += 10;
	c += 5;
}

int main()
{
	printf("Dentro de main:\n");
	printf(" g = %d\n", g);
	functionA();
	functionB();
	functionA();
	functionB();
	printf("\nFinal en main:\n");
	printf(" g = %d\n", g);
	return 0;
}

/**
 * Dentro de main:
 *  g = 10
 *
 * Dentro de functionA:
 *  g = 10
 *  a = 20
 *  b = 30
 *
 * Dentro de functionB:
 *  g = 15
 *  a = 40
 *  c = 50
 *
 * Dentro de functionA:
 *  g = 20
 *  a = 20
 *  b = 35
 *
 * Dentro de functionB:
 *  g = 25
 *  a = 40
 *  c = 55
 *
 * Final en main:
 *  g = 30
 */