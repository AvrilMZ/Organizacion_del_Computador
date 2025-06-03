#include <stdint.h>
#include <stdlib.h>

typedef struct s_array
{
	type_t type;
	uint8_t size;
	uint8_t capacity;
	void **data;
} array_t;

typedef enum e_type
{
	TypeNone = 0,
	TypeInt = 1,
	TypeString = 2,
	TypeCard = 3
} type_t;

array_t *map(array_t *array, void *(*func)(void *))
{
	array_t *nuevo = calloc(1, sizeof(array_t));
	if (!nuevo)
	{
		return NULL;
	}
	nuevo->type = array->type;
	nuevo->size = array->size;
	nuevo->capacity = array->capacity;

	nuevo->data = calloc(array->size, sizeof(void *));
	if (!nuevo->data)
	{
		free(nuevo);
		return NULL;
	}

	for (uint8_t i = 0; i < array->size; i++)
	{
		nuevo->data[i] = func(array->data[i]);
	}

	return nuevo;
}