#include "merge.h"

void intercala(int *vetor, int tamanho1, int tamanho2)
{
    /*  Armazenando o tamanho total do valor para evitar fazer a
        soma sempre que for necessário (reduzindo complexidade)  */
    int tamanhototal = tamanho1 + tamanho2;
    int *backup = (int *)calloc(tamanhototal, sizeof(int));

    /*  vetor 1 = primeira metade do vetor recebido (tamanho/2 arredondado para cima)
        vetor 2 = restante do vetor recebido

        Lidando com os 3 casos na hora de intercalar o vetor:
        Ainda há elementos nos dois vetores;    */

    int i = 0, k = 0;   /*  Nossas variáveis para percorrer os vetores.
                            i percorre o vetor 1 e k percorre o vetor 2    */
    for (; i < tamanho1 && k < tamanho2;)
    {
        if (vetor[i] <= vetor[k + tamanho1])
        {
            backup[i + k] = vetor[i];
            i++;
        }
        else
        {
            backup[i + k] = vetor[k + tamanho1];
            k++;
        }
    }

    /*  Acabaram-se os elementos do vetor 2 (k == tamanho2) e é necessário
    copiar todo o restante do vetor 1 no backup */
    if (k == tamanho2 && i < tamanho1)
    {
        for (; i + k < (tamanhototal); i++)
        {
            backup[i + k] = vetor[i];
        }

    }
    /*  Acabaram-se os elementos do vetor 1 (i == tamanho1 e é necessário
    copiar todo o restante do vetor 2 no backup */
    else
    {
        for (; i + k < (tamanhototal); k++)
        {
            backup[i + k] = vetor[k + tamanho1];
        }
    }

    //  Passando o vetor backup para o vetor original
    for (i = 0; i < tamanhototal; i++)
    {
        vetor[i] = backup[i];
    }
    free(backup);
}

void merge(int *vetor, int tamanho)
{
    //  tamanho 1 = metade do vetor arredondada pra cima
    //  tamanho 2 = restante do vetor
    int tamanho1 = ceil(tamanho/2), tamanho2 = tamanho - tamanho1;

    if (tamanho > 1)
    {
        merge(&vetor[0], tamanho1);
        merge(&vetor[tamanho1], tamanho2);
        intercala(vetor, tamanho1, tamanho2);
    }
}

