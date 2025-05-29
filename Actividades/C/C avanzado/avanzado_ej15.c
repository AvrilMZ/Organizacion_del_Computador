#include <stdint.h>
#include <stdlib.h>

typedef enum e_type
{
	TypeFAT32 = 0,
	TypeEXT4 = 1,
	TypeNTFS = 2
} type_t;

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

typedef struct list
{
	type_t type;
	uint8_t size;
	node_t *first;
} list_t;

node_t *nodo_anterior(list_t *lista, int indice)
{
	if (!lista || lista->size < 2 || indice >= lista->size)
	{
		return NULL;
	}

	node_t *anterior_nodo = lista->first;
	for (int i = 0; i < indice - 1; i++)
	{
		anterior_nodo = anterior_nodo->next;
	}
	return anterior_nodo;
}

list_t *intercambiar_nodos(list_t *lista, int indice1, int indice2)
{
	if (!lista || lista->size < 2)
	{
		return lista;
	}

	node_t *anterior_nodo1;
	node_t *anterior_nodo2;
	node_t *aux_nodo1;
	node_t *aux_nodo2;

	if (indice1 == 0)
	{
		anterior_nodo1 = NULL;
		aux_nodo1 = lista->first;
	}
	else
	{
		anterior_nodo1 = nodo_anterior(lista, indice1);
		aux_nodo1 = anterior_nodo1->next;
	}

	if (indice2 == 0)
	{
		anterior_nodo2 = NULL;
		aux_nodo2 = lista->first;
	}
	else
	{
		anterior_nodo2 = nodo_anterior(lista, indice2);
		aux_nodo2 = anterior_nodo2->next;
	}

	node_t *aux_sig1 = aux_nodo1->next;
	node_t *aux_sig2 = aux_nodo2->next;

	aux_nodo1->next = aux_sig2;
	aux_nodo2->next = aux_sig1;

	if (anterior_nodo1 != NULL)
	{
		anterior_nodo1->next = aux_nodo2;
	}
	else
	{
		lista->first = aux_nodo2;
	}

	if (anterior_nodo2 != NULL)
	{
		anterior_nodo2->next = aux_nodo1;
	}
	else
	{
		lista->first = aux_nodo1;
	}

	return lista;
}