#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "josefo.h"

int main()
{
    int num_casos;
    scanf("%d\n", &num_casos);

    for (int i = 1; i <= num_casos; i++)
    {
        lista_t *l = cria_lista();

        int num_pessoas, constante;
        scanf("%d %d", &num_pessoas, &constante);

        for (int j = 1; j <= num_pessoas; j++)
        {
            insere_lista(l, j);
        }

        int sobrevivente = josefo(l, 1, constante);

        printf("Caso %d: %d\n", i, sobrevivente);

        libera_lista(l);
    }

    return 0;
}



