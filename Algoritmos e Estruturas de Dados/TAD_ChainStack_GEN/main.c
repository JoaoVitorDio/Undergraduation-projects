#include <stdio.h>
#include "pilha.h"

int main()
{
    pilha_t *pilhinha = cria_pilha();
    
    push_pilha(pilhinha, 5);
    push_pilha(pilhinha, 3);
    push_pilha(pilhinha, 4);
    push_pilha(pilhinha, 5);
    push_pilha(pilhinha, 2);
    push_pilha(pilhinha, 7);
    push_pilha(pilhinha, 10);
    
    printf("%d\n", tamanho_pilha(pilhinha));
    
    int x;
    int tamanho = tamanho_pilha(pilhinha);
    while (tamanho)
    {
        pop_pilha(pilhinha, &x);
        tamanho = tamanho_pilha(pilhinha);
        printf("Elemento pop:%d\tTamanho: %d\n", x, tamanho);
    }
    
    libera_pilha(pilhinha);
    
    return 0;
}