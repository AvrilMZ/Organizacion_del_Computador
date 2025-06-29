#include "estadisticas.h"
#include <stdio.h>
#include <string.h>

#define READ 'R'
#define WRITE 'W'
#define HIT '1'

const char *CLEAN_MISS = "2a";
const char *DIRTY_MISS = "2b";
const int KB = 1024;

void inicializar_estadisticas(estadisticas_t *est)
{
	if (!est)
	{
		return;
	}
	*est = (estadisticas_t){0};
}

void actualizar_operacion(estadisticas_t *est, char tipo)
{
	if (!est)
	{
		return;
	}

	est->total++;
	if (tipo == READ)
	{
		est->loads++;
	}
	else if (tipo == WRITE)
	{
		est->stores++;
	}
}

void actualizar_hit(estadisticas_t *est, int es_lectura)
{
	if (!est)
	{
		return;
	}

	if (es_lectura)
	{
		est->read_time += 1;
	}
	else
	{
		est->write_time += 1;
	}
}

void actualizar_miss(estadisticas_t *est, int es_lectura, int es_dirty, int tam_bloque)
{
	est->bytes_read += tam_bloque;
	if (es_lectura)
	{
		est->rmiss++;
		if (es_dirty)
		{
			est->bytes_written += tam_bloque;
			est->read_time += 1 + 2 * 100;
			est->dirty_rmiss++;
		}
		else
		{
			est->read_time += 1 + 100;
		}
	}
	else
	{
		est->wmiss++;
		if (es_dirty)
		{
			est->bytes_written += tam_bloque;
			est->write_time += 1 + 2 * 100;
			est->dirty_wmiss++;
		}
		else
		{
			est->write_time += 1 + 100;
		}
	}
}

void imprimir_estadisticas(const estadisticas_t *est, int C, int E, int S)
{
	if (E == 1)
	{
		fprintf(stdout, "direct-mapped, %i sets, size = %iKB\n", S, C / KB);
	}
	else
	{
		fprintf(stdout, "%i-way, %i sets, size = %iKB\n", E, S, C / KB);
	}
	fprintf(stdout, "loads %i stores %i total %i\n", est->loads, est->stores, est->total);
	fprintf(stdout, "rmiss %i wmiss %i total %i\n", est->rmiss, est->wmiss, est->rmiss + est->wmiss);
	fprintf(stdout, "dirty rmiss %i dirty wmiss %i\n", est->dirty_rmiss, est->dirty_wmiss);
	fprintf(stdout, "bytes read %i bytes written %i\n", est->bytes_read, est->bytes_written);
	fprintf(stdout, "read time %i write time %i\n", est->read_time, est->write_time);
	fprintf(stdout, "miss rate %.6f\n", (double)(est->rmiss + est->wmiss) / est->total);
}

/**
 * Imprime una linea para el caso de ser hit.
 */
void imprimir_linea_hit(int indice_op, int set_index, unsigned int tag,
			int linea_index, int linea_tag, int valid_bit,
			int dirty_bit, int last_used, int mostrar_last_used)
{
	if (linea_tag == -1)
	{
		if (mostrar_last_used)
		{
			fprintf(stdout, "%i %c %x %x %i -1 %i %i %i\n",
				indice_op, HIT, set_index, tag, linea_index, valid_bit, dirty_bit, last_used);
		}
		else
		{
			fprintf(stdout, "%i %c %x %x %i -1 %i %i\n",
				indice_op, HIT, set_index, tag, linea_index, valid_bit, dirty_bit);
		}
	}
	else
	{
		if (mostrar_last_used)
		{
			fprintf(stdout, "%i %c %x %x %i %x %i %i %i\n",
				indice_op, HIT, set_index, tag, linea_index, (unsigned int)linea_tag, valid_bit, dirty_bit, last_used);
		}
		else
		{
			fprintf(stdout, "%i %c %x %x %i %x %i %i\n",
				indice_op, HIT, set_index, tag, linea_index, (unsigned int)linea_tag, valid_bit, dirty_bit);
		}
	}
}

/**
 * Imprime una linea para el caso de ser miss.
 */
void imprimir_linea_miss(char *caso_str, int indice_op, int set_index, unsigned int tag,
			 int linea_index, int linea_tag, int valid_bit,
			 int dirty_bit, int last_used, int mostrar_last_used)
{
	if (!caso_str)
	{
		return;
	}

	if (linea_tag == -1)
	{
		if (mostrar_last_used)
		{
			fprintf(stdout, "%i %s %x %x %i -1 %i %i %i\n",
				indice_op, caso_str, set_index, tag, linea_index, valid_bit, dirty_bit, last_used);
		}
		else
		{
			fprintf(stdout, "%i %s %x %x %i -1 %i %i\n",
				indice_op, caso_str, set_index, tag, linea_index, valid_bit, dirty_bit);
		}
	}
	else
	{
		if (mostrar_last_used)
		{
			fprintf(stdout, "%i %s %x %x %i %x %i %i %i\n",
				indice_op, caso_str, set_index, tag, linea_index, (unsigned int)linea_tag, valid_bit, dirty_bit, last_used);
		}
		else
		{
			fprintf(stdout, "%i %s %x %x %i %x %i %i\n",
				indice_op, caso_str, set_index, tag, linea_index, (unsigned int)linea_tag, valid_bit, dirty_bit);
		}
	}
}

void imprimir_estadisticas_verboso(int indice_op, char caso, int set_index, unsigned int tag,
				   int linea_index, int linea_tag, int valid_bit,
				   int dirty_bit, int last_used, int mostrar_last_used)
{
	if (caso == HIT)
	{
		imprimir_linea_hit(indice_op, set_index, tag, linea_index, linea_tag, valid_bit, dirty_bit, last_used, mostrar_last_used);
	}
	else
	{
		char caso_str[3];
		strcpy(caso_str, CLEAN_MISS);
		if (valid_bit && dirty_bit)
		{
			caso_str[1] = DIRTY_MISS[1];
		}

		imprimir_linea_miss(caso_str, indice_op, set_index, tag, linea_index, linea_tag, valid_bit, dirty_bit, last_used, mostrar_last_used);
	}
}