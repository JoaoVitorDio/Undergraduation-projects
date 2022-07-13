#include <stdio.h>
#include "lista.h"

int main()
{
    lista_t *listinha = cria_lista();
    
    insere_lista(listinha, 5);
    insere_lista(listinha, 3);
    insere_lista(listinha, 4);
    insere_lista(listinha, 5);
    insere_lista(listinha, 2);
    insere_lista(listinha, 7);
    insere_lista(listinha, 10);
    
    imprime_lista(listinha);
    
    inverte_lista(listinha);
    imprime_lista(listinha);
    inverte_lista(listinha);
    
    retira_lista(listinha, 2);
    imprime_lista(listinha);
    
    retira_lista(listinha, 5);
    imprime_lista(listinha);
    
    retira_lista(listinha, 10);
    imprime_lista(listinha);
    
    inverte_lista(listinha);
    imprime_lista(listinha);
    
    libera_lista(listinha);
    
    return 0;
}