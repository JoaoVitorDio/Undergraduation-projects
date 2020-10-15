/*  Conversor de decimal para binário feito na disciplina de
    Algoritmos e Estrutura de Dados -   Exemplo de uso de pilha   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pilha.h"

//  Recebe um inteiro positivo em decimal e retorna um unsigned long int
unsigned long long converte(unsigned int decimal);

int main()
{
    int decimal;
    printf("Digite o numero decimal: ");
    scanf("%d", &decimal);

    unsigned long long binario = converte(decimal);
    printf("\nBinario: %llu\n", binario);

    return 0;
}

unsigned long long converte(unsigned int decimal)
{
    pilha p1;
    pilha_cria(&p1);

    int quociente = 2, tamanho_vetor = 0;
    while (quociente > 1)
    {
        quociente = decimal / 2;
        int resto = decimal % 2;
        pilha_push(&p1, resto);
        tamanho_vetor++;
        decimal = quociente;
    }
    pilha_push(&p1, quociente);
    tamanho_vetor++;

    int *vetor = (int *) calloc(tamanho_vetor, sizeof(int));
    for (int i = 0; i < tamanho_vetor; i++)
    {
        pilha_pop(&p1, &vetor[i]);
    }

    /*  transformando o vetor de numeros binarios em um numero decimal, por meio de
        multiplicações de cada casa decimal por seu respectivo valor na base 10     */
    unsigned long long binario = 0;
    for (int i = 0; i < tamanho_vetor; i++)
    {
        binario += vetor[i] * pow(10, tamanho_vetor - i - 1);
    }

    free(vetor);
    pilha_destroy(&p1);

    return binario;
}