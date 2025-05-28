#include <stdlib.h>
#include <string.h>

typedef struct persona
{
	char *nombre;
	unsigned edad;
} persona_t;

/**
 * Devuelve un puntero a un dato tipo `persona_t` con el nombre y edad pasados por parametro asignados.
 *
 * En caso de error al reservar memoria se devuelve NULL.
 */
persona_t *crearPersona(char *nombre, unsigned edad)
{
	if (!nombre)
	{
		return NULL;
	}

	persona_t *persona = calloc(1, sizeof(persona_t));
	if (!persona)
	{
		return NULL;
	}

	size_t largo_nombre = strlen(nombre);
	persona->nombre = calloc(largo_nombre + 1, sizeof(char));
	if (!persona->nombre)
	{
		free(persona);
		return NULL;
	}

	strcpy(persona->nombre, nombre);
	persona->edad = edad;

	return persona;
}

int main()
{
	persona_t *persona = crearPersona("Maria", 33);
	free(persona->nombre);
	free(persona);

	return 0;
}