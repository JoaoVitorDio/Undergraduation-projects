#include "pilha.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*  TAD pilha implementado usando conceitos de lista encadeada e dinâmica.
    Ocupa apenas a memória usada no programa, alocando-a conforme a necessidade.
    Não necessariamente possui os nós alocados sequencialmente em memória.
    Código feito por JoaoVitorDio para a disciplina de Algoritmos e Estrutura
    de Dados.   */

typedef struct node
{
    elem info;
    struct node *next;
}   node_t;

struct pilha
{
    node_t *topo;
    int tam;
};

pilha_t *cria_pilha()
{
    pilha_t *l = (pilha_t *) calloc(1, sizeof(pilha_t));
    assert(l != NULL);

    l -> topo = NULL;
    l -> tam = 0;

    return l;
}

void libera_pilha(pilha_t *l)
{
    if (l != NULL)
    {
        while (l -> topo != NULL)
        {
            node_t *p = l -> topo;
            l -> topo = p -> next;
            free(p);
        }
    }
    free(l);
}

int push_pilha(pilha_t *l, elem x)
{
    assert(l != NULL);

    node_t *p = (node_t *) calloc(1, sizeof(node_t));
    p -> info = x;
    p -> next = l -> topo;
    l -> topo = p;

    (l -> tam)++;

    return 0;
}

int pop_pilha(pilha_t *l, elem *x)
{
    assert(l != NULL);
    node_t *p = l -> topo;
    *x = p -> info;
    l -> topo = l -> topo -> next;
    (l -> tam)--;
    free(p);

    return 1;
}

int retira_pilha(pilha_t *l, elem x)
{

    //  Nossa função retira funcionará retirando todos os elementos da pilha
    //  que sejam iguais ao argumento. Ou seja, se houver mais de um, serão retirados
    //  todos e não só o que estiver primeiro na pilha.

    assert(l != NULL);

    if (!esta_na_pilha(l, x))
    {
        return 0;   //  Indicando que não há valor para retirar da pilha
    }
    node_t *p = l -> topo;
    node_t *ant = NULL;
    //  ant = variável que apontará sempre para o anterior de p na pilha

    while (p != NULL)
    {
        if (p -> info == x)
        {
            //  Na função retira, também teremos 3 casos:
            //  1° caso: O item a ser retirado é o primeiro, logo, teremos de
            //  atualizar o valor de l -> topo
            if (p == l -> topo)
            {
                //  Nesse momento, p está apontando para l -> topo
                l -> topo = p -> next;
                free(p);
                p = l -> topo;   //  Fazendo p percorrer a pilha para procurar outra ocorrência
            }
            //  2° caso: O item a ser retirado é o último e teremos de atualizar
            //  o valor de ant -> next para NULL.
            else if (p -> next == NULL)
            {
                ant -> next = NULL;
                free(p);
                //  Chegamos ao fim, logo, não há mais nenhum elemento
                //  e devemos retornar 1, já que agora temos p apontando para algum lixo
                //  e não podemos entrar no loop outra vez.

                (l -> tam)--;
                return 1;
            }
            //  3° caso: O item a ser retirado está no meio da pilha
            //  e temos de fazer uma ponte entre o endereço apontado por ant
            //  e o nó em p -> next, para não quebrar a "corrente" da pilha.
            else
            {
                ant -> next = p -> next;
                free(p);
                p = ant -> next;    //  Fazendo p percorrer a pilha para procurar outra ocorrência
            }
            (l -> tam)--;
        }
        else
        {
            ant = p;
            p = p -> next;
        }
    }
    return 1;   //  Indicando que um valor foi retirado da pilha com sucesso
}

int tamanho_pilha(pilha_t *l)
{
    assert(l != NULL);

    return l -> tam;
}

int esta_na_pilha(pilha_t *l, elem x)
{
    assert(l != NULL);

    node_t *p = l -> topo;
    while (p != NULL)
    {
        if (p -> info == x)
        {
            return 1;
        }
        p = p -> next;
    }

    return 0;
}

void imprime_pilha(pilha_t *l)
{
    assert(l != NULL);

    node_t *p = l -> topo;

    while (p != NULL)
    {
        printf("%d ", p -> info);
        p = p -> next;
    }
    printf("\n");
}

void inverte_pilha(pilha_t *l)
{
    assert(l != NULL);

    int tamanho = l -> tam;

    elem *array = (elem *) calloc(tamanho, sizeof(elem));
    node_t *p = l -> topo;

    for (int i = 0; i < tamanho; i++)
    {
        array[i] = p -> info;
        p = p -> next;
    }

    p = l -> topo;
    for (int i = tamanho - 1; i >= 0; i--)
    {
        p -> info = array[i];
        p = p -> next;
    }

    free(array);
}
