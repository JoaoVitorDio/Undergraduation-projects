#include "selection.h"

void selection(int *vetor, int tamanho)
{
    int i, j, min;

    // i é o ponto no vetor de onde começar a fazer comparações, como o selection ordena do começo até o fim.
    for (i = 0; i < tamanho - 1; i++) 
    {
        // Procura o menor elemento a partir do i.
        min = i;
        for (j = i + 1; j < tamanho; j++) 
        {
            if (vetor[j] < vetor[min]) 
            {
                min = j;
            }
        }

        if (min != i) 
        {
            swap(&vetor[i], &vetor[min]);
        }
    }
}

void swap(int *a, int *b) 
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}