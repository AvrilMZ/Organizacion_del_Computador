#include <stdint.h>
#include <stdlib.h>

typedef struct node_str
{
	struct node_str *siguiente;
	int32_t valor;
} node_t;

extern node_t *agregarAdelante_asm(int32_t valor, node_t *siguiente);
extern int32_t valorEn(uint32_t indice, node_t *cabeza);
extern void destruirLista(node_t *cabeza);

node_t *agregarAdelante(int32_t valor, node_t *siguiente)
{
	node_t *adelante = calloc(1, sizeof(node_t));
	if (!adelante)
	{
		return NULL;
	}
	adelante->siguiente = siguiente;
	adelante->valor = valor;
	return adelante;
}