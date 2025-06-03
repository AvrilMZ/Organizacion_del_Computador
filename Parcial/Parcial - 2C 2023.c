#include <stdlib.h>

typedef struct s_list
{
	int size;
	struct s_listElem *first;
	struct s_listElem *last;
} list_t;

typedef struct s_listElem
{
	char c;
	struct s_listElem *next;
} listElem_t;

void sumaElemento(list_t *lista, char index, char new)
{
	listElem_t *nuevo = calloc(1, sizeof(listElem_t));
	if (!nuevo)
	{
		return;
	}
	nuevo->c = new;

	listElem_t *nodo = lista->first;
	for (int i = 0; i < lista->size; i++)
	{
		if (nodo->c == index)
		{
			nuevo->next = nodo->next;
			nodo->next = nuevo;
			if (i == lista->size - 1)
			{
				lista->last = nuevo;
			}
			lista->size++;
		}
		nodo = nodo->next;
	}
}