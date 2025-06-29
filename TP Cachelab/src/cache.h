#ifndef CACHE_H
#define CACHE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct cache cache_t;

/**
 * Inicializa una estructura 'cache_t' con:
 *      - el tamaño de cache 'C';
 *      - la cantidad de líneas por set 'E';
 *      - el número de sets 'S';
 *      - y el tamaño de bloque dados.
 */
cache_t *crear_cache(int C, int E, int S, int tam_bloque);

/**
 * Busca una dirección en la cache:
 *      - devuelve índice de línea si hit;
 *      - -1 si miss.
 */
int buscar_cache(cache_t *cache, unsigned int direccion, int *tag_out, int *set_index_out);

/**
 * Inserta o actualiza un bloque en la cache para una dirección dada, respetando política LRU y actualizando dirty bit si es escritura.
 */
void insertar_cache(cache_t *cache, unsigned int direccion, int es_lectura, int dirty, int indice_op);

/**
 * Actualiza el LRU para la línea usada en un set dado.
 */
void actualizar_lru(cache_t *cache, int set_index, int linea_index, int indice_op);

/**
 * Verifica si una línea específica es válida.
 */
bool es_linea_valida(const cache_t *cache, int set_index, int linea_index);

/**
 * Verifica si una línea específica está dirty.
 */
bool es_linea_dirty(const cache_t *cache, int set_index, int linea_index);

/**
 * Obtiene el tag de una línea específica.
 */
int obtener_tag_linea(const cache_t *cache, int set_index, int linea_index);

/**
 * Obtiene el valor LRU de una línea específica.
 */
int obtener_lru_linea(const cache_t *cache, int set_index, int linea_index);

/**
 * Busca una línea inválida en un set específico.
 *
 * Devuelve el índice de la línea o -1 si no encuentra ninguna.
 */
int buscar_linea_invalida(const cache_t *cache, int set_index);

/**
 * Encuentra la línea menos recientemente usada en un set específico.
 *
 * Devuelve el índice de la línea.
 */
int encontrar_lru(const cache_t *cache, int set_index);

/**
 * Establece el estado dirty de una línea.
 */
void establecer_dirty(cache_t *cache, int set_index, int linea_index, int dirty);

/**
 * Destruye y libera toda la memoria asociada a una estructura 'cache_t'.
 */
void destruir_cache(cache_t *cache);

#endif // CACHE_H_