#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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

typedef void *(*funcCopy_t)(void *);
typedef void (*funcRm_t)(void *);
typedef void (*funcPrint_t)(void *);
funcCopy_t getCopyFunction(type_t t);
funcRm_t getRmFunction(type_t t);

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

funcCopy_t getCopyFunction(type_t t)
{
	switch (t)
	{
	case TypeFAT32:
		return (funcCopy_t)copy_fat32;
		break;
	case TypeEXT4:
		return (funcCopy_t)copy_ext4;
		break;
	case TypeNTFS:
		return (funcCopy_t)copy_ntfs;
		break;
	default:
		return NULL;
		break;
	}
}
funcRm_t getRmFunction(type_t t)
{
	switch (t)
	{
	case TypeFAT32:
		return (funcRm_t)rm_fat32;
		break;
	case TypeEXT4:
		return (funcRm_t)rm_ext4;
		break;
	case TypeNTFS:
		return (funcRm_t)rm_ntfs;
		break;
	default:
		return NULL;
		break;
	}
}

funcPrint_t getPrintFunction(type_t t)
{
	switch (t)
	{
	case TypeFAT32:
		return (funcPrint_t)print_fat32;
		break;
	case TypeEXT4:
		return (funcPrint_t)print_ext4;
		break;
	case TypeNTFS:
		return (funcPrint_t)print_ntfs;
		break;
	default:
		return NULL;
		break;
	}
}

list_t *listNew(type_t type)
{
	list_t *l = malloc(sizeof(list_t));
	l->type = type;
	l->size = 0;
	l->first = NULL;
	return l;
}

void listAddFirst(list_t *l, void *data)
{
	node_t *n = malloc(sizeof(node_t));
	n->data = getCopyFunction(l->type)(data);
	n->next = l->first;
	l->first = n;
	l->size++;
}

uint8_t listSize(list_t *l)
{
	return l->size;
}

int listIsEmpty(list_t *l)
{
	return l->size == 0;
}

void *listFirst(list_t *l)
{
	if (l->first == NULL)
		return NULL;
	return l->first->data;
}

void *listRemoveFirst(list_t *l)
{
	if (l->first == NULL)
		return NULL;

	node_t *nodeToRemove = l->first;
	void *data = nodeToRemove->data;
	l->first = nodeToRemove->next;
	l->size--;
	free(nodeToRemove);
	return data;
}

void print_fat32(fat32_t *f)
{
	printf("FAT32: %u\n", *f);
}

void print_ext4(ext4_t *e)
{
	printf("EXT4: %u\n", *e);
}

void print_ntfs(ntfs_t *n)
{
	printf("NTFS: %u\n", *n);
}

void listPrint(list_t *l)
{
	printf("Lista tipo %d, tamaño: %d\n", l->type, l->size);
	node_t *current = l->first;
	funcPrint_t printFunc = getPrintFunction(l->type);

	while (current != NULL)
	{
		printFunc(current->data);
		current = current->next;
	}
	printf("\n");
}

void listDelete(list_t *l)
{
	node_t *n = l->first;
	while (n)
	{
		node_t *tmp = n;
		n = n->next;
		getRmFunction(l->type)(tmp->data);
		free(tmp);
	}
	free(l);
}