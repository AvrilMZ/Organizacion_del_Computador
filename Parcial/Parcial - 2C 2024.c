#include <stdlib.h>
#include <stdio.h>

#define SIGUIENTE " -> "
#define ULTIMO "NULL"

typedef struct node
{
	struct node *next;
	int data;
} node_t;

typedef struct list
{
	node_t *first;
	node_t *last;
	int size;
} list_t;

list_t *create_list();
void add_node(list_t *list, int data);
void destroy_list(list_t *list);

extern void stringify(FILE *fp, list_t *list);

void stringify_c(FILE *fp, list_t *list)
{
	if (!list || list->size == 0)
	{
		fprintf(fp, ULTIMO);
		return;
	}

	node_t *nodo = list->first;
	for (int i = 0; i < list->size; i++)
	{
		fprintf(fp, "%i", nodo->data);
		if (i != list->size - 1)
		{
			fprintf(fp, SIGUIENTE);
			nodo = nodo->next;
		}
		else
		{
			fprintf(fp, SIGUIENTE);
			fprintf(fp, ULTIMO);
		}
	}
}

int main()
{
	list_t *lista = create_list();
	if (!lista)
	{
		return -1;
	}

	for (int i = 0; i < 3; i++)
	{
		add_node(lista, i);
	}

	stringify(stdout, lista);
	destroy_list(lista);

	return 0;
}