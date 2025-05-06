#include <stdio.h>

int main()
{
	int a = 5, b = 3, c = 2, d = 1;
	printf("Op 1: %i\n", a + b * c / d);
	printf("Op 2: %i\n", a % b);
	printf("Op 3: %i, %i\n", a == b, a != b);
	printf("Op 4: %x, %x\n", a & b, a | b);
	printf("Op 5: %i\n", ~a);
	printf("Op 6: %i, %i\n", a && b, a || b);
	printf("Op 7: %x\n", a << 1);
	printf("Op 8: %x\n", a >> 1);

	int temp = a;
	printf("Op 9a: %i\n", temp += b);
	temp = a;
	printf("Op 9b: %i\n", temp -= b);
	temp = a;
	printf("Op 9c: %i\n", temp *= b);
	temp = a;
	printf("Op 9d: %i\n", temp /= b);
	temp = a;
	printf("Op 9e: %i\n", temp %= b);

	return 0;
}