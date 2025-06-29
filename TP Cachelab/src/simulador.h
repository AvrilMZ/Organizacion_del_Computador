#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "cache.h"
#include "estadisticas.h"

typedef struct simulador simulador_t;

/**
 * Inicializa el simulador con parámetros de cache:
 *      - el tamaño de cache 'C';
 *      - la cantidad de líneas por set 'E';
 *      - el número de sets 'S';
 *      - y el tamaño de bloque dados.
 *
 * Devuelve un puntero a la estructura del simulador.
 */
simulador_t *crear_simulador(int C, int E, int S, int tam_bloque);

/**
 * Simula un acceso a la cache con la dirección y el tipo de operación.
 * Actualiza las estadísticas internas.
 */
void simular_acceso(simulador_t *sim, unsigned int direccion, int es_lectura, int indice_op);

/**
 * Simula un acceso a la caché y recopila información para el modo verboso.
 *
 * Realiza la misma operación que 'simular_acceso' pero además proporciona información detallada.
 */
void simular_acceso_verboso(simulador_t *sim, unsigned int direccion, int es_lectura, int indice_op, int E);

/**
 * Obtiene las estadísticas de un 'simulador_t'.
 */
const estadisticas_t *obtener_estadisticas(const simulador_t *sim);

/**
 * Destruye y libera toda la memoria asociada a una estructura 'simulador_t'.
 */
void destruir_simulador(simulador_t *sim);

#endif // SIMULADOR_H