#include <stdlib.h>

typedef struct persona
{
	char *nombre;
	unsigned edad;
} persona_t;

/**
 * Libera la memoria reservada para un tipo de dato `persona_t`.
 */
void eliminarPersona(persona_t *persona)
{
	if (!persona)
	{
		return;
	}
	free(persona->nombre);
	free(persona);
}