#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "lib.h"

const int TIPO_CARTA = 3;

/**
 * Crea un mazo en forma de array con cinco cartas de ejemplo.
 */
array_t *array_crear_mazo_cinco_cartas()
{
    array_t *mazo = arrayNew(TIPO_CARTA, 5);
    int32_t num1 = 1;
    int32_t num7 = 7;

    card_t *elementos[5];
    elementos[0] = cardNew("Espadas", &num1);
    elementos[1] = cardNew("Bastos", &num1);
    elementos[2] = cardNew("Espadas", &num7);
    elementos[3] = cardNew("Oros", &num7);
    elementos[4] = cardNew("Copas", &num1);

    for (int i = 0; i < 5; i++)
    {
        arrayAddLast(mazo, &elementos[i]);
        mazo->size++;
    }
    return mazo;
}

/**
 * Imprime el mazo.
 */
void array_imprimir_mazo(array_t *mazo, FILE *pFile)
{
    if (!mazo || !pFile)
    {
        return;
    }

    for (int i = 0; i < mazo->size; i++)
    {
        cardPrint(mazo->data[i], pFile);
    }
}

/**
 * Crea un mazo en forma de lista con cinco cartas de ejemplo.
 */
list_t *lista_crear_mazo_cinco_cartas()
{
    list_t *mazo = listNew(TIPO_CARTA);
    int32_t num1 = 1;
    int32_t num7 = 7;

    card_t *elementos[5];
    elementos[0] = cardNew("Espadas", &num1);
    elementos[1] = cardNew("Bastos", &num1);
    elementos[2] = cardNew("Espadas", &num7);
    elementos[3] = cardNew("Oros", &num7);
    elementos[4] = cardNew("Copas", &num1);

    for (int i = 0; i < 5; i++)
    {
        listAddLast(mazo, elementos[i]);
        mazo->size++;
    }
    return mazo;
}

/**
 * Imprime el mazo.
 */
void list_imprimir_mazo(list_t *mazo, FILE *pFile)
{
    if (!mazo || !pFile)
    {
        return;
    }

    for (int i = 0; i < mazo->size; i++)
    {
        cardPrint(listGet(mazo, i), pFile);
    }
}

int main(void)
{
    // ---------------- Array ----------------
    array_t *array_cartas = array_crear_mazo_cinco_cartas();

    array_imprimir_mazo(array_cartas, stdout);

    int8_t cero = 0;
    int8_t uno = 1;
    card_t *carta_base = arrayGet(array_cartas, cero);
    card_t *carta_a_apilar = arrayGet(array_cartas, uno);
    cardAddStacked(carta_base, carta_a_apilar);

    array_imprimir_mazo(array_cartas, stdout);

    arrayDelete(array_cartas);

    // ---------------- List ----------------
    list_t *list_cartas = lista_crear_mazo_cinco_cartas();

    list_imprimir_mazo(list_cartas, stdout);

    card_t *carta_base1 = listGet(list_cartas, cero);
    card_t *carta_a_apilar1 = listGet(list_cartas, uno);
    cardAddStacked(carta_base1, carta_a_apilar1);

    list_imprimir_mazo(list_cartas, stdout);

    listDelete(list_cartas);

    return 0;
}