#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

typedef struct
{
        int loads;
        int stores;
        int total;
        int rmiss;
        int wmiss;
        int dirty_rmiss;
        int dirty_wmiss;
        int bytes_read;
        int bytes_written;
        int read_time;
        int write_time;
} estadisticas_t;

/**
 * Inicializa una estructura 'estadisticas_t' con todos sus campos en cero.
 */
void inicializar_estadisticas(estadisticas_t *est);

/**
 * Actualiza el contador de operaciones del tipo dado y el total.
 */
void actualizar_operacion(estadisticas_t *est, char tipo);

/**
 * Incrementa el tiempo de acceso correspondiente en caso de hit.
 */
void actualizar_hit(estadisticas_t *est, int es_lectura);

/**
 * Actualiza las métricas correspondientes en caso de miss.
 *
 * Aumenta del contador de misses de lectura o escritura.
 * Aumenta de tiempo total según si fue dirty miss o no.
 * Aumenta de los bytes leídos (y escritos si es dirty miss de escritura).
 */
void actualizar_miss(estadisticas_t *est, int es_lectura, int es_dirty, int tam_bloque);

/**
 * Imprime por pantalla todas las estadisticas.
 */
void imprimir_estadisticas(const estadisticas_t *est, int C, int E, int S);

/**
 * Imprime por pantalla todas las estadisticas del modo verboso.
 */
void imprimir_estadisticas_verboso(int indice_op, char caso, int set_index, unsigned int tag,
                                   int linea_index, int line_tag, int valid_bit,
                                   int dirty_bit, int last_used, int mostrar_last_used);

#endif // ESTADISTICAS_H_