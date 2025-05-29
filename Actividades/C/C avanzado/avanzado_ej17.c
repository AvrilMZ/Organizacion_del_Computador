#include <stdlib.h>
#include <stdint.h>

typedef uint32_t fat32_t;
typedef uint32_t ext4_t;
typedef uint32_t ntfs_t;

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

fat32_t *new_fat32()
{
	fat32_t *f = malloc(sizeof(fat32_t));
	*f = 123; // Valor random
	return f;
}

fat32_t *copy_fat32(fat32_t *original)
{
	fat32_t *copia = malloc(sizeof(fat32_t));
	*copia = *original;
	return copia;
}

void rm_fat32(fat32_t *f)
{
	free(f);
}

ext4_t *new_ext4()
{
	ext4_t *e = malloc(sizeof(ext4_t));
	*e = 456; // Valor random
	return e;
}

ext4_t *copy_ext4(ext4_t *original)
{
	ext4_t *copia = malloc(sizeof(ext4_t));
	*copia = *original;
	return copia;
}

void rm_ext4(ext4_t *e)
{
	free(e);
}

ntfs_t *new_ntfs()
{
	ntfs_t *n = malloc(sizeof(ntfs_t));
	*n = 789; // Valor random
	return n;
}

ntfs_t *copy_ntfs(ntfs_t *original)
{
	ntfs_t *copia = malloc(sizeof(ntfs_t));
	*copia = *original;
	return copia;
}

void rm_ntfs(ntfs_t *n)
{
	free(n);
}

list_t *listNew(type_t t)
{
	list_t *l = malloc(sizeof(list_t));
	l->type = t; // l->type es equivalente a (*l).type
	l->size = 0;
	l->first = NULL;
	return l;
}

void listAddFirst(list_t *l, void *data)
{
	node_t *n = malloc(sizeof(node_t));
	switch (l->type)
	{
	case TypeFAT32:
		n->data = (void *)copy_fat32((fat32_t *)data);
		break;
	case TypeEXT4:
		n->data = (void *)copy_ext4((ext4_t *)data);
		break;
	case TypeNTFS:
		n->data = (void *)copy_ntfs((ntfs_t *)data);
		break;
	}
	n->next = l->first;
	l->first = n;
	l->size++;
}

// se asume: i < l->size
void *listGet(list_t *l, uint8_t i)
{
	node_t *n = l->first;
	for (uint8_t j = 0; j < i; j++)
		n = n->next;
	return n->data;
}

// se asume: i < l->size
void *listRemove(list_t *l, uint8_t i)
{
	node_t *tmp = NULL;
	void *data = NULL;
	if (i == 0)
	{
		data = l->first->data;
		tmp = l->first;
		l->first = l->first->next;
	}
	else
	{
		node_t *n = l->first;
		for (uint8_t j = 0; j < i - 1; j++)
			n = n->next;
		data = n->next->data;
		tmp = n->next;
		n->next = n->next->next;
	}
	free(tmp);
	l->size--;
	return data;
}

void listDelete(list_t *l)
{
	node_t *n = l->first;
	while (n)
	{
		node_t *tmp = n;
		n = n->next;
		switch (l->type)
		{
		case TypeFAT32:
			rm_fat32((fat32_t *)tmp->data);
			break;
		case TypeEXT4:
			rm_ext4((ext4_t *)tmp->data);
			break;
		case TypeNTFS:
			rm_ntfs((ntfs_t *)tmp->data);
			break;
		}
		free(tmp);
	}
	free(l);
}

int main()
{
	list_t *lista = listNew(TypeFAT32);

	fat32_t valor1 = 123;
	fat32_t valor2 = 456;
	listAddFirst(lista, &valor1);
	listAddFirst(lista, &valor2);

	void *data_removida = listRemove(lista, 0);

	// rm_fat32((fat32_t*)data_removida);
	// listDelete(lista);

	return 0;
}

/**
 * HEAP SUMMARY:
 * 	in use at exit: 40 bytes in 4 blocks
 * 	total heap usage: 5 allocs, 1 frees, 56 bytes allocated
 *
 * LEAK SUMMARY:
 * 	definitely lost: 20 bytes in 2 blocks
 * 	indirectly lost: 20 bytes in 2 blocks
 * 	  possibly lost: 0 bytes in 0 blocks
 * 	still reachable: 0 bytes in 0 blocks
 * 	     suppressed: 0 bytes in 0 blocks
 *
 * ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
 */