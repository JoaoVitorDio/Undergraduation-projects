#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "josefo.h"

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

    if (esta_na_lista(l, x) == 1)
    {
        return 0;
    }

    if (l -> sentinel == NULL)
    {
        l -> sentinel = (node_t *) calloc(1, sizeof(node_t));
        assert (l -> sentinel != NULL);

        l -> sentinel -> info = x;
        l -> sentinel -> next = l -> sentinel;
    }
    else
    {
        node_t *aux = l -> sentinel;
        node_t *p = (node_t *) calloc(1, sizeof(node_t));
        assert (p != NULL);

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
        if (p -> info == x)
        {
            if (p == l -> sentinel)
            {
                ant -> next = l -> sentinel -> next;
                free(p);
                p = ant -> next;
                l -> sentinel = p;
            }
            else
            {
                ant -> next = p -> next;
                free(p);
                p = ant -> next;
            }
            (l -> tam)--;
        }
        else
        {
            ant = p;
            p = p -> next;
        }
    }


    return 0;
}

int tamanho_lista(lista_t *l)
{
    assert (l != NULL);

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
    //  colocando o sentinel na posicao do soldado1
    for (int i = 0; i < l -> tam; i++)
    {
        if (l -> sentinel -> info == soldado1)
        {
            break;
        }
        else
        {
            l -> sentinel = l -> sentinel -> next;
        }
    }
    //  colocando um anterior de p e p um a frente do sentinel
    //  (pulamos o sentinel na primeira contagem)
    node_t *ant = l -> sentinel;
    node_t *p = l -> sentinel -> next;


    while (1)
    {
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

    return l -> sentinel -> info;
}
