#include "simulador.h"

#define READ 'R'
#define WRITE 'W'
#define HIT '1'

struct simulador
{
        cache_t *cache;
        estadisticas_t estadisticas;
        int tam_bloque;
};

simulador_t *crear_simulador(int C, int E, int S, int tam_bloque)
{
        simulador_t *sim = (simulador_t *)calloc(1, sizeof(simulador_t));
        if (!sim)
        {
                return NULL;
        }

        sim->cache = crear_cache(C, E, S, tam_bloque);
        if (!sim->cache)
        {
                free(sim);
                return NULL;
        }

        inicializar_estadisticas(&sim->estadisticas);
        sim->tam_bloque = tam_bloque;

        return sim;
}

/**
 * Maneja el caso de que el acceso sea un hit.
 */
void manejar_hit(simulador_t *sim, int set_index, int linea_index, int es_lectura, int indice_op)
{
        actualizar_hit(&sim->estadisticas, es_lectura);

        if (es_lectura)
        {
                actualizar_lru(sim->cache, set_index, linea_index, indice_op);
        }
        else
        {
                establecer_dirty(sim->cache, set_index, linea_index, 1);
                actualizar_lru(sim->cache, set_index, linea_index, indice_op);
        }
}

/**
 * Maneja el caso de que el acceso sea un miss.
 */
void manejar_miss(simulador_t *sim, unsigned int direccion, int es_lectura, int set_index, int indice_op)
{
        int victima_index = -1;

        if (es_lectura)
        {
                victima_index = buscar_linea_invalida(sim->cache, set_index);
                if (victima_index == -1)
                {
                        victima_index = encontrar_lru(sim->cache, set_index);
                }
        }
        else
        {
                victima_index = encontrar_lru(sim->cache, set_index);
        }

        int desalojo_fue_sucio = 0;
        if (es_linea_valida(sim->cache, set_index, victima_index) &&
            es_linea_dirty(sim->cache, set_index, victima_index))
        {
                desalojo_fue_sucio = 1;
        }

        actualizar_miss(&sim->estadisticas, es_lectura, desalojo_fue_sucio, sim->tam_bloque);
        int nuevo_dirty_status = !es_lectura;
        insertar_cache(sim->cache, direccion, es_lectura, nuevo_dirty_status, indice_op);
}

void simular_acceso(simulador_t *sim, unsigned int direccion, int es_lectura, int indice_op)
{
        if (es_lectura)
        {
                actualizar_operacion(&sim->estadisticas, READ);
        }
        else
        {
                actualizar_operacion(&sim->estadisticas, WRITE);
        }

        int tag;
        int set_index;
        int linea_index = buscar_cache(sim->cache, direccion, &tag, &set_index);
        if (linea_index != -1)
        {
                manejar_hit(sim, set_index, linea_index, es_lectura, indice_op);
        }
        else
        {
                manejar_miss(sim, direccion, es_lectura, set_index, indice_op);
        }
}

/**
 * Obtiene información sobre una línea de caché específica.
 */
static void obtener_info_linea(simulador_t *sim, int set_index, int linea_index,
                               int *valid_bit, int *dirty_bit, int *line_tag, int *last_used)
{
        if (es_linea_valida(sim->cache, set_index, linea_index))
        {
                *valid_bit = 1;
                *dirty_bit = es_linea_dirty(sim->cache, set_index, linea_index);
                *line_tag = obtener_tag_linea(sim->cache, set_index, linea_index);
                *last_used = obtener_lru_linea(sim->cache, set_index, linea_index);
        }
        else
        {
                *valid_bit = 0;
                *dirty_bit = 0;
                *line_tag = -1;
                *last_used = 0;
        }
}

/**
 * Determina qué línea de caché debe ser reemplazada en caso de miss.
 *
 * En caso de lectura, primero busca una línea inválida para usar.
 * Si no hay líneas inválidas o es una escritura, usa la LRU.
 */
static int determinar_linea_para_reemplazo(simulador_t *sim, int set_index, int es_lectura)
{
        int indice_reemplazo = -1;
        if (es_lectura)
        {
                indice_reemplazo = buscar_linea_invalida(sim->cache, set_index);
                if (indice_reemplazo == -1)
                {
                        indice_reemplazo = encontrar_lru(sim->cache, set_index);
                }
        }
        else
        {
                indice_reemplazo = encontrar_lru(sim->cache, set_index);
        }

        return indice_reemplazo;
}

void simular_acceso_verboso(simulador_t *sim, unsigned int direccion, int es_lectura, int indice_op, int E)
{
        if (!sim)
        {
                return;
        }

        int tag;
        int set_index;
        int linea_index = buscar_cache(sim->cache, direccion, &tag, &set_index);

        char caso = ' ';
        int line_tag = -1;
        int valid_bit = 0;
        int dirty_bit = 0;
        int last_used = 0;
        int indice_linea_reemplazo = -1;

        if (linea_index != -1)
        {
                caso = HIT;
                obtener_info_linea(sim, set_index, linea_index, &valid_bit, &dirty_bit, &line_tag, &last_used);
        }
        else
        {
                indice_linea_reemplazo = determinar_linea_para_reemplazo(sim, set_index, es_lectura);
                obtener_info_linea(sim, set_index, indice_linea_reemplazo, &valid_bit, &dirty_bit, &line_tag, &last_used);
                linea_index = indice_linea_reemplazo;
        }

        imprimir_estadisticas_verboso(indice_op, caso, set_index, tag,
                                      linea_index, line_tag, valid_bit,
                                      dirty_bit, last_used, E > 1);

        simular_acceso(sim, direccion, es_lectura, indice_op);
}

const estadisticas_t *obtener_estadisticas(const simulador_t *sim)
{
        if (!sim)
        {
                return NULL;
        }
        return &sim->estadisticas;
}

void destruir_simulador(simulador_t *sim)
{
        if (!sim)
        {
                return;
        }
        destruir_cache(sim->cache);
        free(sim);
}