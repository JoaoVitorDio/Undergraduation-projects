#include "pilha.h"
#include <stdlib.h>
#include <assert.h>

/*  Tipo abstrato de dados: Pilha
    Funções escritas uma a uma para exercitar o conceito, e também a prática da linguagem.
    Esse código foi importante para estudar o uso e desenvolvimento de TADs e "bibliotecas",
    tanto que foi a primeira aplicação do "makefile" nos nossos códigos (alunos).   */

void pilha_cria(pilha *p1)
{
    p1 -> topo = -1;
    p1 -> vetor = (int *) calloc(1, sizeof(int));
}

void pilha_pop(pilha *p1, int *x)
{
    (*x) = p1 -> vetor[p1 -> topo];
    (p1 -> topo)--;
}

void pilha_push(pilha *p1, int x)
{
    (p1 -> topo)++;
    p1 -> vetor = (int *) realloc(p1 -> vetor, ((p1 -> topo) + 1) * sizeof(int));
    assert(p1 -> vetor != NULL);
    p1 -> vetor[p1 -> topo] = x;
}

void pilha_empty(pilha *p1)
{
    free(p1 -> vetor);
    //  Enviando a pilha todo como argumento porque nosso ponteiro p1 já armazena o seu endereço
    pilha_cria(p1);
}

void pilha_destroy(pilha *p1)
{
    if (p1 != NULL)
    {
        if (p1 -> vetor != NULL)
        {
            free(p1 -> vetor);
            p1 -> topo = 0;
        }
    }
}

unsigned char pilha_is_empty(pilha *p1)
{
    if (p1 -> topo == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//  Funcao intermediaria usada na funcao pilha_inverte
void swap (int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

//  Visto que nossa pilha é sequencial e dinâmica, podemos invertê-la
//  facilmente usando os índices dos vetores.
void pilha_inverte(pilha *p1)
{
    //  Topo armazena o indice do ultimo elemento da pilha, logo
    //  topo + 1 representa a quantia de elementos
    int tamanho = (p1 -> topo) + 1;
    int half = tamanho / 2;
    for (int i = 0; i < half; i++)
    {
        swap(&(p1 -> vetor[i]), &(p1 -> vetor[tamanho - i -1]));
    }
}