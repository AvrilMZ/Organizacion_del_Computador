#include <stdint.h>

#define NAME_LEN 21

typedef struct cliente_str
{
	char nombre[NAME_LEN];
	char apellido[NAME_LEN];
	uint64_t compra;
	uint32_t dni;
} cliente_t;

typedef struct __attribute__((__packed__)) packed_cliente_str
{
	char nombre[NAME_LEN];
	char apellido[NAME_LEN];
	uint64_t compra;
	uint32_t dni;
} __attribute__((packed)) packed_cliente_t;

/*
`cliente_t`:
	Offset:  0    8   16   24   32   40   48   56
		|----|----|----|----|----|----|----|----|
		|    nombre[0-7]    |    nombre[8-15]   |
		|----|----|----|----|----|----|----|----|
		|  nombre[16-20] +  |   apellido[0-2]   |
		|  3 bytes padding  |                   |
		|----|----|----|----|----|----|----|----|
		|   apellido[3-10]  |  apellido[11-18]  |
		|----|----|----|----|----|----|----|----|
		|  apellido[19-20]  | compra (uint64_t) |
		|   + 6 bytes pad   |                   |
		|----|----|----|----|----|----|----|----|
		|      compra       |   dni (uint32_t)  |
		|                   |   + 4 bytes pad   |
		|----|----|----|----|----|----|----|----|
	Total: 64 bytes

`packed_cliente_t`:
	Offset:  0    8   16   24   32   40   48   56
		|----|----|----|----|----|----|----|----|
		|    nombre[0-7]    |   nombre[8-15]    |
		|----|----|----|----|----|----|----|----|
		|   nombre[16-20]   |   apellido[0-3]   |
		|----|----|----|----|----|----|----|----|
		|   apellido[4-11]  |   apellido[12-19] |
		|----|----|----|----|----|----|----|----|
		|    apellido[20]   | compra (uint64_t) |
		|----|----|----|----|----|----|----|----|
		|      compra       |   dni (uint32_t)  |
		|----|----|----|----|----|----|----|----|
	Total: 50 bytes
*/