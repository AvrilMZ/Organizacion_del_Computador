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
	struct node *before;
} node_t;

typedef struct list
{
	type_t type;
	uint8_t size;
	node_t *first;
	node_t *last;
} list_t;

void listAddLast(list_t *l, void *data)
{
	if (!l)
	{
		return;
	}

	node_t *nodo_nuevo = calloc(1, sizeof(node_t));
	if (!nodo_nuevo)
	{
		return;
	}
	nodo_nuevo->data = data;

	if (l->size == 0)
	{
		l->first = nodo_nuevo;
		l->last = nodo_nuevo;
		nodo_nuevo->before = NULL;
	}
	else
	{
		nodo_nuevo->before = l->last;
		l->last->next = nodo_nuevo;
		l->last = nodo_nuevo;
	}
	l->size++;
}