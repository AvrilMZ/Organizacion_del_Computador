#include "cache.h"
#include <math.h>

#define MISS -1

typedef struct
{
        int valid;
        int dirty;
        int tag;
        int last_used;
} linea_t;

typedef struct
{
        linea_t *lineas;
} set_t;

struct cache
{
        set_t *sets;
        int C;
        int E;
        int S;
        int block_size;
};

cache_t *crear_cache(int C, int E, int S, int tam_bloque)
{
        if (C <= 0 || E <= 0 || S <= 0 || tam_bloque <= 0)
        {
                return NULL;
        }

        cache_t *cache = calloc(1, sizeof(cache_t));
        if (!cache)
        {
                return NULL;
        }
        cache->block_size = tam_bloque;
        cache->C = C;
        cache->E = E;
        cache->S = S;
        cache->sets = calloc(cache->S, sizeof(set_t));
        if (!cache->sets)
        {
                free(cache);
                return NULL;
        }

        for (int i = 0; i < cache->S; i++)
        {
                cache->sets[i].lineas = calloc(cache->E, sizeof(linea_t));
                if (!cache->sets[i].lineas)
                {
                        for (int j = 0; j < i; j++)
                        {
                                free(cache->sets[j].lineas);
                        }
                        free(cache->sets);
                        free(cache);
                        return NULL;
                }
        }

        return cache;
}

int buscar_cache(cache_t *cache, unsigned int direccion, int *tag_out, int *set_index_out)
{
        if (!cache || !tag_out || !set_index_out)
        {
                return MISS;
        }

        int bits_set_index = (int)log2(cache->S);
        int bits_block_offset = (int)log2(cache->block_size);
        int tag = direccion >> (bits_set_index + bits_block_offset);
        int set_index = (direccion >> bits_block_offset) & ((1 << bits_set_index) - 1);
        *set_index_out = set_index;
        *tag_out = tag;

        int i = 0;
        int linea_buscada = MISS;
        while (i < cache->E && linea_buscada == MISS)
        {
                if (cache->sets[set_index].lineas[i].valid && cache->sets[set_index].lineas[i].tag == *tag_out)
                {
                        linea_buscada = i;
                }
                i++;
        }

        return linea_buscada;
}

/**
 * Inicializa los campos de un 'linea_t' con el 'tag' dado.
 */
void inicializar_linea_cache(linea_t *linea, int tag)
{
        linea->valid = 1;
        linea->dirty = 0;
        linea->tag = tag;
        linea->last_used = 0;
}

/**
 * Devuelve el indice del bloque LRU.
 */
int last_recently_used_block(set_t set, int cant_lineas)
{
        int lru_block_index = 0;
        for (int i = 1; i < cant_lineas; i++)
        {
                if (set.lineas[i].last_used < set.lineas[lru_block_index].last_used)
                {
                        lru_block_index = i;
                }
        }
        return lru_block_index;
}

void insertar_cache(cache_t *cache, unsigned int direccion, int es_lectura, int dirty, int indice_op)
{
        if (!cache)
        {
                return;
        }

        int set_index;
        int tag;
        int linea_index = buscar_cache(cache, direccion, &tag, &set_index);
        if (linea_index != -1)
        {
                if (!es_lectura)
                {
                        cache->sets[set_index].lineas[linea_index].dirty = dirty;
                }
                actualizar_lru(cache, set_index, linea_index, indice_op);
                return;
        }

        int bloque_a_reemplazar = buscar_linea_invalida(cache, set_index);
        if (bloque_a_reemplazar == -1)
        {
                bloque_a_reemplazar = encontrar_lru(cache, set_index);
        }

        inicializar_linea_cache(&cache->sets[set_index].lineas[bloque_a_reemplazar], tag);

        if (!es_lectura)
        {
                cache->sets[set_index].lineas[bloque_a_reemplazar].dirty = dirty;
        }

        actualizar_lru(cache, set_index, bloque_a_reemplazar, indice_op);
}

void actualizar_lru(cache_t *cache, int set_index, int linea_index, int indice_op)
{
        if (!cache)
        {
                return;
        }
        cache->sets[set_index].lineas[linea_index].last_used = indice_op;
}

/**
 * Devuelve true si los datos por parámetro son válidos, en caso contrario false.
 */
bool indices_validos(const cache_t *cache, int set_index, int linea_index)
{
        return (cache && set_index >= 0 && set_index < cache->S &&
                linea_index >= 0 && linea_index < cache->E);
}

bool es_linea_valida(const cache_t *cache, int set_index, int linea_index)
{
        if (!indices_validos(cache, set_index, linea_index))
        {
                return false;
        }
        return cache->sets[set_index].lineas[linea_index].valid;
}

bool es_linea_dirty(const cache_t *cache, int set_index, int linea_index)
{
        if (!indices_validos(cache, set_index, linea_index))
        {
                return false;
        }
        return cache->sets[set_index].lineas[linea_index].dirty;
}

int obtener_tag_linea(const cache_t *cache, int set_index, int linea_index)
{
        if (!cache || set_index < 0 || set_index >= cache->S || linea_index < 0 || linea_index >= cache->E)
        {
                return -1;
        }

        if (!cache->sets[set_index].lineas[linea_index].valid)
        {
                return -1;
        }

        return cache->sets[set_index].lineas[linea_index].tag;
}

int obtener_lru_linea(const cache_t *cache, int set_index, int linea_index)
{
        if (!cache || set_index < 0 || set_index >= cache->S || linea_index < 0 || linea_index >= cache->E)
        {
                return -1;
        }
        return cache->sets[set_index].lineas[linea_index].last_used;
}

int buscar_linea_invalida(const cache_t *cache, int set_index)
{
        if (!cache || set_index < 0 || set_index >= cache->S)
        {
                return -1;
        }

        for (int i = 0; i < cache->E; i++)
        {
                if (!cache->sets[set_index].lineas[i].valid)
                {
                        return i;
                }
        }
        return -1;
}

int encontrar_lru(const cache_t *cache, int set_index)
{
        if (!cache || set_index < 0 || set_index >= cache->S)
        {
                return -1;
        }

        int lru_index = 0;
        for (int i = 1; i < cache->E; i++)
        {
                if (cache->sets[set_index].lineas[i].last_used < cache->sets[set_index].lineas[lru_index].last_used)
                {
                        lru_index = i;
                }
        }
        return lru_index;
}

void establecer_dirty(cache_t *cache, int set_index, int linea_index, int dirty)
{
        if (!cache || set_index < 0 || set_index >= cache->S || linea_index < 0 || linea_index >= cache->E)
        {
                return;
        }
        cache->sets[set_index].lineas[linea_index].dirty = dirty;
}

void destruir_cache(cache_t *cache)
{
        if (!cache)
        {
                return;
        }

        for (int i = 0; i < cache->S; i++)
        {
                free(cache->sets[i].lineas);
        }
        free(cache->sets);
        free(cache);
}