#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Faça um programa em C que receba o nome do método de ordenação
    (no caso, selecao ou bolha) e o número N de elementos de um vetor.
    Após isso, leia os N elementos e imprima as indicações de todas as
    comparações e trocas realizadas pelo método escolhido, seguido do vetor ordenado.

    As comparações e trocas devem ser impressas de acordo com os índices
    dos elementos envolvidos na operação. Por exemplo, se o elemento do
    índice 3 foi comparado com o elemento do índice 7, então deve-se
    imprimir C 3 7. Se o elemento de índice 2 foi trocado com o elemento
    de índice 5, deve-se imprimir T 2 5.
*/

void troca(int *p1, int *p2);
void bubble(int tamanho, int *vetor);
void selection(int tamanho_vetor, int *vetor);

int main()
{
	char seleciona[10];
	scanf("%s", seleciona);

	int tamanho;
	scanf("%d ", &tamanho);

	int *vetor = (int *) calloc(tamanho, sizeof(int));

	for (int i = 0; i < tamanho; i++)
	{
		scanf("%d", &vetor[i]);
	}	
	
	if (strcmp(seleciona, "bolha") == 0)
	{
		bubble(tamanho, &vetor[0]);
	}	else if (strcmp(seleciona, "selecao") == 0)
	{
		selection(tamanho, &vetor[0]);
	}

	for (int i = 0; i < tamanho; i++)
	{
		printf("%d ", vetor[i]);
	}
	printf("\n");

	return 0;
}

void troca(int *p1, int *p2)
{
	int backup = (*p1);
	*p1 = *p2;
	*p2 = backup;
}

void bubble(int tamanho, int *vetor)
{
	int ultima_troca = tamanho;

	while (tamanho > 1)
	{
		for (int i = 0; i + 1 < tamanho; i++)
		{
			printf("C %d %d\n", i, i + 1);
			if(vetor[i] > vetor[i + 1])
			{
				printf("T %d %d\n", i, i + 1);
				troca(&vetor[i], &vetor[i + 1]);
				ultima_troca = i + 1;
			}
		}
		tamanho = ultima_troca;
	}

}

void selection(int tamanho_vetor, int *vetor)
{
	int posicao_minimo = 0;
	for (int i = 0; i < tamanho_vetor; i++)
	{
		posicao_minimo = i;
		for (int j = i; j < tamanho_vetor; j++)
		{
			printf("C %d %d\n", posicao_minimo, j);
			if (vetor[j] < vetor[posicao_minimo])
			{
				posicao_minimo = j;
			}
		}

		troca(&vetor[i], &vetor[posicao_minimo]);
		printf("T %d %d\n", i, posicao_minimo);
	}
}



