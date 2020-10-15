#include "lista.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*  TAD lista implementado usando conceitos de lista encadeada e dinâmica.
    Ocupa apenas a memória usada no programa, alocando-a conforme a necessidade.
    Não necessariamente possui os nós alocados sequencialmente em memória.
    Código feito por JoaoVitorDio para a disciplina de Algoritmos e Estrutura
    de Dados.

    Utiliza-se do tipo "elem" definido em lista.h. Adaptável a qualquer tipo básico
    de dado da linguagem C, porém, apresenta problemas com structs que contenham ponteiros,
    sendo necessário utilizar-se de um TAD com ponteiros void para esses casos.    */

typedef struct node
{
    elem info;
    struct node *next;
}   node_t;

struct lista
{
    node_t *ini, *fim;
    int tam;
};

lista_t *cria_lista()
{
    lista_t *l = (lista_t *) calloc(1, sizeof(lista_t));
    assert(l != NULL);

    l -> ini = NULL;
    l -> fim = NULL;
    l -> tam = 0;

    return l;
}

void libera_lista(lista_t *l)
{
    if (l != NULL)
    {
        while (l -> ini != NULL)
        {
            node_t *p = l -> ini;
            l -> ini = p -> next;
            free(p);
        }
    }
    free(l);
}

int insere_lista(lista_t *l, elem x)
{
    assert(l != NULL);
    //  Ao inserir elementos na lista, podemos nos deparar com alguns casos:
    //  1° caso: A lista está vazia, logo, ini aponta para NULL;
    node_t *p = (node_t *) calloc(1, sizeof(node_t));
    p -> info = x;
    p -> next = NULL;

    if (l -> ini == NULL)
    {
        l -> ini = p;
        l -> fim = p;
    }
    //  2° caso: A lista já possui algum elemento.
    else    //  Inseriremos o elemento no fim da lista.
    {
        l -> fim -> next = p;
        l -> fim = p;
    }

    (l -> tam)++;

    return 0;
}

int retira_lista(lista_t *l, elem x)
{

    //  Nossa função retira funcionará retirando todos os elementos da lista
    //  que sejam iguais ao argumento. Ou seja, se houver mais de um, serão retirados
    //  todos e não só o primeiro.

    assert(l != NULL);

    if (!esta_na_lista(l, x))
    {
        return 0;   //  Indicando que não há valor para retirar da lista
    }
    node_t *p = l -> ini;
    node_t *ant = NULL;
    //  ant = variável que apontará sempre para o anterior de p na lista

    while (p != NULL)
    {
        if (p -> info == x)
        {
            //  Na função retira, também teremos 3 casos:
            //  1° caso: O item a ser retirado é o primeiro, logo, teremos de
            //  atualizar o valor de l -> ini
            if (p == l -> ini)
            {
                //  Nesse momento, p está apontando para l -> ini
                l -> ini = p -> next;
                free(p);
                p = l -> ini;   //  Fazendo p percorrer a lista para procurar outra ocorrência
            }
            //  2° caso: O item a ser retirado é o último e teremos de atualizar
            //  o valor de l -> fim. Usaremos o laço atualizando o valor de p
            //  até chegar em p = fim, para termos o valor certo em ant
            else if (p == l -> fim)
            {
                ant -> next = NULL;
                l -> fim = ant;
                free(p);
                //  Chegamos ao fim, logo, não há mais nenhum elemento
                //  e devemos retornar 1, já que agora temos p apontando para algum lixo
                //  e não podemos entrar no loop outra vez.

                (l -> tam)--;
                return 1;
            }
            //  3° caso: O item a ser retirado está no meio da lista
            //  e temos de fazer uma ponte entre o endereço apontado por ant
            //  e o nó em p -> next, para não quebrar a "corrente" da lista.
            else
            {
                ant -> next = p -> next;
                free(p);
                p = ant -> next;    //  Fazendo p percorrer a lista para procurar outra ocorrência
            }
            (l -> tam)--;
        }
        else
        {
            ant = p;
            p = p -> next;
        }
    }
    return 1;   //  Indicando que um valor foi retirado da lista com sucesso
}

int tamanho_lista(lista_t *l)
{
    assert(l != NULL);

    return l -> tam;
}

int esta_na_lista(lista_t *l, elem x)
{
    assert(l != NULL);

    node_t *p = l -> ini;
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

void imprime_lista(lista_t *l)
{
    assert(l != NULL);

    node_t *p = l -> ini;

    while (p != NULL)
    {
        printf("%d ", p -> info);
        p = p -> next;
    }
    printf("\n");
}

void inverte_lista(lista_t *l)
{
    assert(l != NULL);

    int tamanho = l -> tam;

    elem *array = (elem *) calloc(tamanho, sizeof(elem));
    node_t *p = l -> ini;

    for (int i = 0; i < tamanho; i++)
    {
        array[i] = p -> info;
        p = p -> next;
    }

    p = l -> ini;
    for (int i = tamanho - 1; i >= 0; i--)
    {
        p -> info = array[i];
        p = p -> next;
    }

    free(array);
}
