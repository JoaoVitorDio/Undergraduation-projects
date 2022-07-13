#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "josefo.h"

int main()
{
    lista_t *l = cria_lista();
    insere_lista(l, 5);
    insere_lista(l, 0);
    insere_lista(l, 1);
    insere_lista(l, 4);
    insere_lista(l, 3);
    insere_lista(l, 2);
    insere_lista(l, 6);

    printf("Na lista circular: ");
    imprime_lista(l);

    time_t t;
    srand((unsigned) time(&t));

    int m = rand() % 7;
    int gap = rand() % 7;
    int soldado = josefo(l, m, gap);

    printf("com m = %d e gap = %d...\n", m, gap);
    printf("O soldado que ira buscar reforços e: %d\n", soldado);

    libera_lista(l);
    return 0;
}



