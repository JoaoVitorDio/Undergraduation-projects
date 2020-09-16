#include <stdio.h>
#include <stdlib.h>

/*
Faça um programa em C que leia um vetor V e indique qual é a posição do menor valor.

As entradas para o programa são números inteiros, da seguinte forma:

N # Número de elementos do vetor

N inteiros # cada uma dos elementos do vetor. Ou seja, V[0], V[1], V[2], ..., V[N-1]

A saída é um inteiro, correspondente ao índice i, tal que V[i] seja o menor valor do vetor.
Em caso de valores iguais, considere o menor valor.
*/

int main()
{
    int tamanho, *vetor;

    scanf("%d", &tamanho);

    vetor = (int *)calloc(tamanho, sizeof(int));

    for (int i = 0; i < tamanho; i++)
    {
        scanf("%d", &vetor[i]);
    }

    int menor = vetor[0];
    int posicao = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (menor > vetor[i])
        {
            menor = vetor[i];
            posicao = i;
        }
    }

    printf("%d\n", posicao);

    return 0;
}