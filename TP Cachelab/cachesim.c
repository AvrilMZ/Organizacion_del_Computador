#include "src/simulador.h"
#include <stdio.h>
#include <stdlib.h>

#define READ 'R'

const int CANT_ARGUMENTOS_VALIDOS[2] = {5, 8};
const int INDICE_ARGV_ARCHIVO = 1;
const int INDICE_ARGV_C = 2;
const int INDICE_ARGV_E = 3;
const int INDICE_ARGV_S = 4;
const int INDICE_ARGV_N = 6;
const int INDICE_ARGV_M = 7;
const char *ERROR = "ERROR\n";
const char *MODO_LECTURA = "r";
const int VALID = 1;
const int CAPACIDAD_INICIAL = 64;

/**
 * Devuelve 1 si el archivo existe, en caso contrario 0.
 */
int archivo_existe(const char *nombre)
{
	FILE *archivo = fopen(nombre, MODO_LECTURA);
	if (archivo == NULL)
	{
		return 0;
	}
	fclose(archivo);
	return 1;
}

/**
 * Devuelve 1 si el número dado es potencia de dos, en caso contrario 0.
 */
int es_potencia_de_dos(int N)
{
	return N > 0 && (N & (N - 1)) == 0;
}

/**
 * Devuelve 1 si el tamaño (C), la asociatividad (E) y el número de sets de la caché (S) son potencias de dos, en caso contrario 0.
 */
int C_E_S_potencias_de_dos(int C, int E, int S)
{
	return es_potencia_de_dos(C) && es_potencia_de_dos(E) && es_potencia_de_dos(S);
}

/**
 * Devuelve 1 si la combinación del tamaño (C), la asociatividad (E) y el número de sets de la caché (S) es válida, en caso contrario 0.
 */
int C_E_S_combinaciones_validas(int C, int E, int S)
{
	if (E <= 0 || S <= 0)
	{
		return 0;
	}

	int divisor = E * S;
	if (divisor == 0 || C % divisor != 0)
	{
		return 0;
	}

	int b = C / divisor;
	return es_potencia_de_dos(b);
}

/**
 * Devuelve 1 si n y m cumplen que 0 ≤ N ≤ M, en caso contrario 0.
 */
int n_m_dentro_parametros(int N, int M)
{
	return N >= 0 && N < M;
}

/**
 * Devuelve el tamaño del bloque (porción de memoria copiada desde RAM a caché).
 */
int tamanio_de_bloque(int C, int E, int S)
{
	return C / (E * S);
}

/**
 * Devuelve true si los argumentos dados por terminal son validos, en caso contrario devuelve false.
 */
bool argumentos_validos(int argc, char *argv[])
{
	if (argc != CANT_ARGUMENTOS_VALIDOS[0] && argc != CANT_ARGUMENTOS_VALIDOS[1])
	{
		return 0;
	}

	if (!archivo_existe(argv[INDICE_ARGV_ARCHIVO]))
	{
		return 0;
	}

	int C = atoi(argv[INDICE_ARGV_C]);
	int E = atoi(argv[INDICE_ARGV_E]);
	int S = atoi(argv[INDICE_ARGV_S]);

	if (!C_E_S_potencias_de_dos(C, E, S) || !C_E_S_combinaciones_validas(C, E, S))
	{
		return 0;
	}

	if (argc == CANT_ARGUMENTOS_VALIDOS[1] &&
	    !n_m_dentro_parametros(atoi(argv[INDICE_ARGV_N]), atoi(argv[INDICE_ARGV_M])))
	{
		return 0;
	}

	return 1;
}

/**
 * Maneja las trazas del archivo dado según el modo solicitado.
 */
void procesar_traza(simulador_t *simulador, FILE *archivo, int modo_verboso,
		    int n, int m, int E)
{
	int indice_op = 0;
	char tipo;
	unsigned int direccion;

	while (fscanf(archivo, "%*x: %c %x %*i %*x", &tipo, &direccion) == 2)
	{
		int es_lectura = (tipo == READ);

		if (modo_verboso && indice_op >= n && indice_op <= m)
		{
			simular_acceso_verboso(simulador, direccion, es_lectura, indice_op, E);
		}
		else
		{
			simular_acceso(simulador, direccion, es_lectura, indice_op);
		}

		indice_op++;
	}
}

int main(int argc, char *argv[])
{
	if (!argumentos_validos(argc, argv))
	{
		fprintf(stderr, "%s", ERROR);
		return -1;
	}

	int C = atoi(argv[INDICE_ARGV_C]);
	int E = atoi(argv[INDICE_ARGV_E]);
	int S = atoi(argv[INDICE_ARGV_S]);
	int tam_bloque = tamanio_de_bloque(C, E, S);

	int modo_verboso = 0;
	int n = 0;
	int m = 0;
	if (argc == CANT_ARGUMENTOS_VALIDOS[1])
	{
		modo_verboso = 1;
		n = atoi(argv[INDICE_ARGV_N]);
		m = atoi(argv[INDICE_ARGV_M]);
	}

	simulador_t *simulador = crear_simulador(C, E, S, tam_bloque);

	FILE *archivo = fopen(argv[INDICE_ARGV_ARCHIVO], MODO_LECTURA);
	if (!archivo)
	{
		fprintf(stderr, "%s", ERROR);
		destruir_simulador(simulador);
		return -1;
	}

	procesar_traza(simulador, archivo, modo_verboso, n, m, E);

	fclose(archivo);

	const estadisticas_t *estadisticas = obtener_estadisticas(simulador);
	imprimir_estadisticas(estadisticas, C, E, S);

	destruir_simulador(simulador);

	return 0;
}