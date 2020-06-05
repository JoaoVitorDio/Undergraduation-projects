/* Faça um programa que acha o maior e o menor inteiro dentro de um vetor de 10 inteiros.
Obs: usar apenas as variáveis a seguir:
int v[10], i, *maior, *menor; */

#include <stdio.h>
#include <conio.h>

int main () {
	
	int vetor[10], i, *maior, *menor;

	for (i = 0; i < 10; i++) {
		printf ("\nDigite o valor a ser colocado na posicao %d do vetor: ", i);
		scanf ("%d", &vetor[i]);
	}
	
	maior = &vetor[0];
	menor = &vetor[0]; // pode ser na posicao 9 também...
	
	for (i=0;i < 10;i++) {
		if (*maior < vetor[i])
			maior = &vetor[i];
		
		if (*menor > vetor[i])
			menor = &vetor[i];
	}
	
	printf ("O maior e: %d\nO menor e: %d", *maior, *menor);

	
	getch ();
	return 0;
}


