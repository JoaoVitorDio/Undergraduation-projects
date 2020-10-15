#include "bubble.h"

void bubble(int *vetor, int tamanho)
{
    int i, j;

    int ultimaTroca;

    i = tamanho - 1;
    // i é o ponto no vetor até onde realizar comparações, como o bubble ordena do fim até o começo.
    while (i > 0)
    {
        ultimaTroca = 0;
        // Percorre o vetor até a posição ainda não ordenada, comparando cada
        // posição com a próxima e as trocando caso a de antes seja maior.
        for (j = 0; j < i; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                ultimaTroca = j;
                swap(&vetor[j], &vetor[j + 1]);
            }
        }
        i = ultimaTroca;
    }
}

void swap(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}