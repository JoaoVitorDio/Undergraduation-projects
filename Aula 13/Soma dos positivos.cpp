#include <stdio.h>
#include <stdlib.h>

int* aloca_memoria (int tamanho);
int soma_positivo (int* v, int tamanho);

/*	Faça um programa que trabalhe com alocação dinâmica de memória, e faça uma função que 
	receba leia um vetor e retorna a soma dos valores positivos desse vetor à main e os exiba	*/

int main () {
	
	int tamanho, *v;
	
	printf ("Digite o tamanho do vetor a ser digitado.\n");
	scanf ("%d", &tamanho);
	
	v = aloca_memoria(tamanho);
	
	printf ("\nA soma dos valores positivos digitados e: %d", soma_positivo(v, tamanho));
	
	free (v);
	
	return 0;
}

int* aloca_memoria (int tamanho) {
	int *v, count;
	
	if (tamanho < 1)
	return NULL;
	v = (int*) calloc (tamanho, sizeof(int));
	if (v == NULL) 
	return NULL;
	
	for (count = 0; count < tamanho; count++) {
		printf ("\nDigite o numero da %d posicao", count+1);
		scanf ("%d", &v[count]);
	}
	
	return v;
}

int soma_positivo (int* v, int tamanho) {
	
	int count, soma = 0;
	
	for (count = 0; count < tamanho; count++) {
		if (v[count] > 0) {
			soma = soma + v[count];
		}
	}
	
	return soma;
}



