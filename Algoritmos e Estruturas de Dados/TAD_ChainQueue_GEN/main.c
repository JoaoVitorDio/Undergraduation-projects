#include <stdio.h>
#include "fila.h"

int main()
{
    fila_t *filinha = cria_fila();

    insere_fila(filinha, 5);
    insere_fila(filinha, 3);
    insere_fila(filinha, 4);
    insere_fila(filinha, 5);
    insere_fila(filinha, 2);
    insere_fila(filinha, 7);
    insere_fila(filinha, 10);

    imprime_fila(filinha);

    while(tamanho_fila(filinha))
    {
        int x;
        
        remove_fila(filinha, &x);
        if (x == 4)
            inverte_fila(filinha);
        printf("%d\n", x);
    }

    libera_fila(filinha);

    return 0;
}