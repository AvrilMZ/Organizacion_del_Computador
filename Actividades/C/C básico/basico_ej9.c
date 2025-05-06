#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t palabra1;
	printf("Ingese la palabra1 a usar: ");
	scanf("%u", &palabra1);

	uint32_t palabra2;
	printf("Ingese la palabra2 a usar: ");
	scanf("%u", &palabra2);

	uint32_t mask_msb = 0xE0000000; // 11100000000000000000000000000000
	uint32_t mask_lsb = 0x7;	// 00000000000000000000000000000111

	uint32_t bits_altos_palabra1 = (palabra1 & mask_msb) >> 29;
	uint32_t bits_bajos_palabra2 = (palabra2 & mask_lsb);

	if (bits_altos_palabra1 == bits_bajos_palabra2)
	{
		printf("Los bits son iguales\n");
	}
	else
	{
		printf("Los bits son diferentes\n");
	}

	return 0;
}