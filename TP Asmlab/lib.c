#include "lib.h"

#define APERTURA_CORCHETES '['
#define COMA ','
#define CIERRE_CORCHETES ']'

funcCmp_t *getCompareFunction(type_t t)
{
	switch (t)
	{
	case TypeInt:
		return (funcCmp_t *)&intCmp;
		break;
	case TypeString:
		return (funcCmp_t *)&strCmp;
		break;
	case TypeCard:
		return (funcCmp_t *)&cardCmp;
		break;
	default:
		break;
	}
	return 0;
}
funcClone_t *getCloneFunction(type_t t)
{
	switch (t)
	{
	case TypeInt:
		return (funcClone_t *)&intClone;
		break;
	case TypeString:
		return (funcClone_t *)&strClone;
		break;
	case TypeCard:
		return (funcClone_t *)&cardClone;
		break;
	default:
		break;
	}
	return 0;
}
funcDelete_t *getDeleteFunction(type_t t)
{
	switch (t)
	{
	case TypeInt:
		return (funcDelete_t *)&intDelete;
		break;
	case TypeString:
		return (funcDelete_t *)&strDelete;
		break;
	case TypeCard:
		return (funcDelete_t *)&cardDelete;
		break;
	default:
		break;
	}
	return 0;
}
funcPrint_t *getPrintFunction(type_t t)
{
	switch (t)
	{
	case TypeInt:
		return (funcPrint_t *)&intPrint;
		break;
	case TypeString:
		return (funcPrint_t *)&strPrint;
		break;
	case TypeCard:
		return (funcPrint_t *)&cardPrint;
		break;
	default:
		break;
	}
	return 0;
}

/** Int **/

int32_t intCmp(int32_t *a, int32_t *b)
{
	if (!a || !b || (*a == *b))
	{
		return 0;
	}
	else if (*a < *b)
	{
		return 1;
	}
	return -1;
}

void intDelete(int32_t *a)
{
	if (!a)
	{
		return;
	}
	free(a);
}

void intPrint(int32_t *a, FILE *pFile)
{
	if (!a || !pFile)
	{
		return;
	}
	fprintf(pFile, "%i", *a);
}

int32_t *intClone(int32_t *a)
{
	if (!a)
	{
		return NULL;
	}

	int32_t *clon = (int32_t *)calloc(1, sizeof(int32_t));
	if (!clon)
	{
		return NULL;
	}
	*clon = *a;
	return clon;
}

/** Lista **/

list_t *listNew(type_t t)
{
	list_t *lista = calloc(1, sizeof(list_t));
	if (!lista)
	{
		return NULL;
	}
	lista->type = t;
	return lista;
}

uint8_t listGetSize(list_t *l)
{
	if (!l)
	{
		return 0;
	}
	return l->size;
}

/**
 * Devuelve el nodo de la lista en el indice dado.
 */
listElem_t *getNodeAtIndex(list_t *l, uint8_t i)
{
	if (!l || i >= l->size)
	{
		return NULL;
	}

	listElem_t *nodo = l->first;
	for (int j = 0; j < i; j++)
	{
		nodo = nodo->next;
	}
	return nodo;
}

void *listGet(list_t *l, uint8_t i)
{
	listElem_t *nodo = getNodeAtIndex(l, i);
	if (!nodo)
	{
		return NULL;
	}
	return nodo->data;
}

/**
 * Devuelve una copia del dato pasado según su tipo.
 */
void *cloneDataByType(void *data, type_t type)
{
	funcClone_t *clone = getCloneFunction(type);
	if (!clone)
	{
		return NULL;
	}
	return clone(data);
}

void listAddFirst(list_t *l, void *data)
{
	if (!l || !data || l->type == 0)
	{
		return;
	}

	listElem_t *nuevo = calloc(1, sizeof(listElem_t));
	if (!nuevo)
	{
		return;
	}

	nuevo->data = cloneDataByType(data, l->type);
	if (!nuevo->data)
	{
		free(nuevo);
		return;
	}

	nuevo->next = l->first;
	if (l->first)
	{
		l->first->prev = nuevo;
	}
	else
	{
		l->last = nuevo;
	}
	l->first = nuevo;
	l->size++;
}

void listAddLast(list_t *l, void *data)
{
	if (!l || !data || l->type == 0)
	{
		return;
	}

	listElem_t *nuevo = calloc(1, sizeof(listElem_t));
	if (!nuevo)
	{
		return;
	}

	nuevo->data = cloneDataByType(data, l->type);
	if (!nuevo->data)
	{
		free(nuevo);
		return;
	}

	nuevo->prev = l->last;
	if (l->last)
	{
		l->last->next = nuevo;
	}
	else
	{
		l->first = nuevo;
	}
	l->last = nuevo;
	l->size++;
}

list_t *listClone(list_t *l)
{
	if (!l)
	{
		return NULL;
	}

	list_t *nueva_lista = calloc(1, sizeof(list_t));
	if (!nueva_lista)
	{
		return NULL;
	}
	nueva_lista->type = l->type;

	listElem_t *nodo_actual = l->first;
	while (nodo_actual)
	{
		listAddLast(nueva_lista, nodo_actual->data);
		nodo_actual = nodo_actual->next;
	}
	return nueva_lista;
}

/**
 * Elimina el dato pasado según su tipo.
 */
void deleteDataByType(void *data, type_t type)
{
	funcDelete_t *eliminar = getDeleteFunction(type);
	if (!eliminar)
	{
		return;
	}
	eliminar(data);
}

void listDeleteData(type_t list_type, listElem_t **elemento_actual)
{
	deleteDataByType((*elemento_actual)->data, list_type);
}

/**
 * Elimina de la lista dada el elemento pasado.
 */
void removeNodeFromList(list_t *l, listElem_t *elemento)
{
	if (elemento == l->first)
	{
		l->first = l->first->next;
		if (l->first)
		{
			l->first->prev = NULL;
		}
		else
		{
			l->last = NULL;
		}
	}
	else if (elemento == l->last)
	{
		l->last = l->last->prev;
		l->last->next = NULL;
	}
	else
	{
		elemento->prev->next = elemento->next;
		elemento->next->prev = elemento->prev;
	}
}

void *listRemove(list_t *l, uint8_t i)
{
	if (!l || i >= l->size)
	{
		return 0;
	}

	void *elemento_eliminado = listGet(l, i);
	void *copia_elemento = cloneDataByType(elemento_eliminado, l->type);

	listElem_t *elemento_actual = getNodeAtIndex(l, i);

	removeNodeFromList(l, elemento_actual);
	listDeleteData(l->type, &elemento_actual);
	free(elemento_actual);
	l->size--;

	return copia_elemento;
}

void listSwap(list_t *l, uint8_t i, uint8_t j)
{
	if (!l || i >= l->size || j >= l->size || i == j)
	{
		return;
	}

	listElem_t *nodo_i = getNodeAtIndex(l, i);
	listElem_t *nodo_j = getNodeAtIndex(l, j);

	if (nodo_i && nodo_j)
	{
		void *temp = nodo_i->data;
		nodo_i->data = nodo_j->data;
		nodo_j->data = temp;
	}
}

void listDelete(list_t *l)
{
	if (!l)
	{
		return;
	}

	listElem_t *actual = l->first;
	while (actual)
	{
		listElem_t *siguiente = actual->next;
		if (actual->data)
		{
			deleteDataByType(actual->data, l->type);
		}

		free(actual);
		actual = siguiente;
	}

	free(l);
}

/**
 * Imprime el dato en el FILE dado según su tipo.
 */
void printDataByType(void *data, type_t type, FILE *pFile)
{
	funcPrint_t *print = getPrintFunction(type);
	if (!print)
	{
		return;
	}
	print(data, pFile);
}

void listPrint(list_t *l, FILE *pFile)
{
	if (!l || !pFile)
	{
		return;
	}

	fprintf(pFile, "%c", APERTURA_CORCHETES);

	bool primero = true;
	listElem_t *nodo_actual = l->first;
	while (nodo_actual)
	{
		if (!primero)
		{
			fprintf(pFile, "%c", COMA);
		}

		printDataByType(nodo_actual->data, l->type, pFile);

		primero = false;
		nodo_actual = nodo_actual->next;
	}
	fprintf(pFile, "%c", CIERRE_CORCHETES);
}

/** Game **/

game_t *gameNew(void *cardDeck, funcGet_t *funcGet, funcRemove_t *funcRemove, funcSize_t *funcSize, funcPrint_t *funcPrint, funcDelete_t *funcDelete)
{
	game_t *game = (game_t *)malloc(sizeof(game_t));
	if (!game)
	{
		return NULL;
	}
	game->cardDeck = cardDeck;
	game->funcGet = funcGet;
	game->funcRemove = funcRemove;
	game->funcSize = funcSize;
	game->funcPrint = funcPrint;
	game->funcDelete = funcDelete;
	return game;
}
int gamePlayStep(game_t *g)
{
	int applied = 0;
	uint8_t i = 0;
	while (applied == 0 && i + 2 < g->funcSize(g->cardDeck))
	{
		card_t *a = g->funcGet(g->cardDeck, i);
		card_t *b = g->funcGet(g->cardDeck, i + 1);
		card_t *c = g->funcGet(g->cardDeck, i + 2);
		if (strCmp(cardGetSuit(a), cardGetSuit(c)) == 0 || intCmp(cardGetNumber(a), cardGetNumber(c)) == 0)
		{
			card_t *removed = g->funcRemove(g->cardDeck, i);
			cardAddStacked(b, removed);
			cardDelete(removed);
			applied = 1;
		}
		i++;
	}
	return applied;
}
uint8_t gameGetCardDeckSize(game_t *g)
{
	return g->funcSize(g->cardDeck);
}
void gameDelete(game_t *g)
{
	g->funcDelete(g->cardDeck);
	free(g);
}
void gamePrint(game_t *g, FILE *pFile)
{
	g->funcPrint(g->cardDeck, pFile);
}
