#include <stdint.h>
#include <stdlib.h>

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

int main()
{
	list_t *l = listNew(TypeFAT32);
	fat32_t *f1 = new_fat32();
	fat32_t *f2 = new_fat32();
	listAddFirst(l, f1);
	listAddFirst(l, f2);
	listDelete(l);
	rm_fat32(f1);
	rm_fat32(f2);
	return 0;
}