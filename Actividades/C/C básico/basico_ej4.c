#include <stdint.h>
#include <stdio.h>

int main()
{
	printf("------------- SIGNED -------------\n");
	printf("Tamaño int8_t: %zu bytes\n", sizeof(int8_t));
	printf("Tamaño int16_t: %zu bytes\n", sizeof(int16_t));
	printf("Tamaño int32_t: %zu bytes\n", sizeof(int32_t));
	printf("Tamaño int64_t: %zu bytes\n", sizeof(int64_t));

	printf("\n------------- UNSIGNED -------------\n");
	printf("Tamaño uint8_t: %zu bytes\n", sizeof(uint8_t));
	printf("Tamaño uint16_t: %zu bytes\n", sizeof(uint16_t));
	printf("Tamaño uint32_t: %zu bytes\n", sizeof(uint32_t));
	printf("Tamaño uint64_t: %zu bytes\n", sizeof(uint64_t));

	return 0;
}