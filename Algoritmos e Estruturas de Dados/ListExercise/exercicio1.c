#include <stdio.h>
#include <stdlib.h>

//  Faça um programa que insere inteiros lidos do teclado em
//  uma lista encadeada e dinâmica até o usuário digitar '-1'.
//  Depois, imprima na tela os elementos que foram armazenados.

typedef struct elemento elemento_t;
struct elemento
{
    int numero;
    elemento_t *next;
};



int main()
{
    elemento_t *inicio = NULL, *fim = NULL;

    while (1)
    {
        elemento_t *operador = (elemento_t *) calloc(1, sizeof(elemento_t));

        scanf("%d", &(operador -> numero));
        if (operador -> numero == -1)
        {
            free(operador);
            break;
        }

        operador -> next = NULL;

        if (inicio == NULL)
        {
            inicio = operador;
            fim = operador;
        }

        fim -> next = operador;
        fim = operador;
    }

    for (int i = 1; inicio != NULL; i++)
    {
        elemento_t *operador = inicio;
        printf("%d° Elemento da lista: %d\n", i, operador -> numero);
        inicio = operador -> next;
        free(operador);
    }

    return 0;
}