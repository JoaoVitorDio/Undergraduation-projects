#include <stdio.h>
#include <stdlib.h>

    /*  Faça um programa que leia um número inteiro e positivo N. Após isso leia N
    números inteiros. Ao fim, imprima 1 se a sequência de números lidos estão ordenados
    em forma crescente e -1 se estão ordenados de forma decrescente. Se não estão
    ordenados, imprima 0. Considere que uma sequência de tamanho N é crescente quando
    X1 <= X2 <= ... <= XN e decrescente quando X1 >= X2 >= ... >= XN. No caso desse
    exercício, se todos os valores lidos forem iguais, considere como um segmento crescente. */

int main()
{
    unsigned int tamanho;

    scanf("%u", &tamanho);

    int *vetor;
    vetor = (int *) calloc(tamanho, sizeof(int));
    if (vetor == NULL)
    {
        return 2;
    }

    for (int i = 0; i < tamanho; i++)
    {
        scanf("%d", &vetor[i]);
    }

    /*  Verificando se é uma sequencia crescente. Setamos a variável como 1, e caso
    encontremos algum valor maior que o valor seguinte, setamos seu valor para 0.
    Isso nos permite economizar processamento e ignorar os casos de valores iguais em uma
    sequencia, como por exemplo, 3 4 4 5, que deve ser considerada crescente. */
    int crescente = 1;
    for (int i = 0; i + 1 < tamanho; i++)
    {
        if (vetor[i] > vetor[i + 1])
        {
            crescente = 0;
            break;
        }
    }

    /*  Verificando se é uma sequencia decrescente. Setamos a variável como 1, e caso
    encontremos algum valor menor que o valor seguinte, setamos seu valor para 0.
    Isso nos permite economizar processamento e ignorar os casos de valores iguais em uma
    sequencia, como por exemplo, 5 4 4 3, que deve ser considerada decrescente. */
    int decrescente = 1;
    for (int i = 0; i + 1 < tamanho; i++)
    {
        if (vetor[i] < vetor[i + 1])
        {
            decrescente = 0;
            break;
        }
    }

    /*  Colocaremos uma verificação adicional para o caso em que todos são iguais, visto
    que ambas verificacoes de decrescente e crescente estariam com valor em 1.  */
    int igual = 1;
    for (int i = 0; i + 1 < tamanho; i++)
    {
        if (vetor[i] != vetor[i+1])
        {
            igual = 0;
        }
    }

    if (crescente == 1 && decrescente == 0)ls
    {
        printf("1\n");
    }
    else if (crescente == 0 && decrescente == 1)
    {
        printf("-1\n");
    }
    else if (igual == 1)
    {
        printf("1\n");
    }
    /*  Nossos casos possíveis são: Crescente, decrescente ou igual. Se não se encaixar
    em nenhum, a única opção possível é que não esteja ordenado.    */
    else
    {
        printf("0\n");
    }



    return 0;
}