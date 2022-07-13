#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "josefo.h"

// Problema adaptado do exercıcio Josephus Problem do VJUDGE.
// Disponivel em: https://vjudge.net/problem/LightOJ-1179

typedef struct node
{
    int info;
    struct node *next;
}   node_t;

struct lista
{
    node_t *sentinel;
    int tam;
};

lista_t *cria_lista()
{
    lista_t *l = (lista_t *) calloc(1, sizeof(lista_t));
    l -> tam = 0;
    l -> sentinel = NULL;

    return l;
}

void libera_lista(lista_t *l)
{
    if (l != NULL)
    {
        node_t *p = l -> sentinel;

        for (int i = 0; i < l -> tam; i++)
        {
            node_t *aux = p -> next;
            free(p);
            p = aux;
        }
    }
    free(l);
}

int insere_lista(lista_t *l, elem x)
{
    assert(l != NULL);

    //  assegurando que não são permitidos elementos repetidos
    if (esta_na_lista(l, x) == 1)
    {
        return 0;
    }

    if (l -> sentinel == NULL)  //  1o caso: lista vazia
    {
        l -> sentinel = (node_t *) calloc(1, sizeof(node_t));
        assert(l -> sentinel != NULL);

        l -> sentinel -> info = x;
        l -> sentinel -> next = l -> sentinel;
    }
    else
    {
        node_t *aux = l -> sentinel;
        node_t *p = (node_t *) calloc(1, sizeof(node_t));
        assert(p != NULL);

        p -> info = x;
        p -> next = l -> sentinel;
        while (1)
        {
            aux = aux -> next;
            if (aux -> next == l -> sentinel)
            {
                break;
            }
        }
        aux -> next = p;
    }
    (l -> tam)++;
    return 1;
}

int retira_lista(lista_t *l, elem x)
{
    assert(l != NULL);

    if (esta_na_lista(l, x) == 0)
    {
        return 0;
    }

    node_t *p = l -> sentinel -> next;
    node_t *ant = l -> sentinel;

    for (int i = 0; i < l -> tam; i++)
    {
        if (p -> info == x) //  se o nosso p estiver apontando para o valor a ser retirado
        {
            if (p == l -> sentinel) //  1o caso: Retirar o sentinel
            {
                ant -> next = l -> sentinel -> next;
                free(p);
                p = ant -> next;
                l -> sentinel = p;
            }
            else    //  2o caso: É um elemento no meio da lista circular
            {
                ant -> next = p -> next;
                free(p);
                p = ant -> next;
            }
            (l -> tam)--;
        }
        else
        {
            //  Se não encontramos ainda e sabemos que está na lista, continuemos a percorrê-la
            ant = p;
            p = p -> next;
        }
    }


    return 0;
}

int tamanho_lista(lista_t *l)
{
    assert(l != NULL);

    return l -> tam;
}

int esta_na_lista(lista_t *l, elem x)
{
    assert(l != NULL);

    node_t *p = l -> sentinel;

    for (int i = 0; i < l -> tam; i++)
    {
        if (p -> info == x)
        {
            return 1;
        }
        p = p -> next;
    }
    return 0;
}
void imprime_lista(lista_t *l)
{
    assert(l != NULL);

    node_t *p = l -> sentinel;
    for (int i = 0; i < (l -> tam); i++)
    {
        printf("%d ", p -> info);
        p = p -> next;
    }
    printf("\n");
}


int josefo(lista_t *l, int soldado1, int random)
{
    assert(l != NULL);

    assert(esta_na_lista(l, soldado1) == 1);

    node_t *ant;
    //  colocando o sentinel na posicao do soldado1 e o ant em seu lugar
    for (int i = 0; i < l -> tam; i++)
    {
        ant = l -> sentinel;
        l -> sentinel = l -> sentinel -> next;
        if (l -> sentinel -> info == soldado1)
        {
            break;
        }
    }

    node_t *p = l -> sentinel;
    while (1)
    {
        //  Se o gap for maior que 1, precisamos andar no vetor
        //  até chegarmos ao próximo soldado morto, e consequentemente
        //  atualizar o ant para que possamos removê-lo
        for (int i = 0; i < random - 1; i++)
        {
            ant = p;
            p = p -> next;
        }
        retira_lista(l, p -> info);
        p = ant -> next;

        if (tamanho_lista(l) <= 1)
        {
            break;
        }
    }
    //  nas retiradas, o sentinela é atualizado e tratado para que
    //  sempre aponte para um elemento da fila. Se a fila ao fim das
    //  mortes possui um unico elemento, o sentinela está apontando
    //  para ele
    return l -> sentinel -> info;
}
