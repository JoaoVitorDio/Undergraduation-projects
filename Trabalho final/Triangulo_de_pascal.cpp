/*	Crie um programa que leia um inteiro n e imprima um triângulo de Pascal com n linhas.	*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
	
	int i, j;
	unsigned short int num_linhas;
	unsigned long int **pascal;		//	Matriz que armazenará os valores do triangulo
	
	printf ("Digite a quantia de linhas do triangulo de Pascal:\n");	//	Interação com o usuario para obter "n"
	scanf ("%u", &num_linhas);
	num_linhas++;						//	O número de linhas a ser impressa é o numero digitado +1, porque há linha 0.
	
	if (num_linhas <= 0) {
		printf ("Nao ha triangulo de Pascal com menos de 1 linha. Saindo do programa...");
		return 0;
	}
	
	pascal = (unsigned long int **) calloc (num_linhas, sizeof(unsigned long int *));	/*	Alocação dinâmica da matriz que armazenará os dados	*/
	if (pascal == NULL) {
		printf ("\nErro ao alocar memoria para os dados.\n");
		return (int)NULL;
	}
	for (i = 0; i < num_linhas; i++) {
		pascal[i] = (unsigned long int *) calloc (i+2, sizeof (unsigned long int));	//	Cada linha receberá uma coluna a mais. Exemplo: a primeira linha 
		if (pascal[i] == NULL) {													//	terá dois valores. Manteremos o ultimo como 0, para usar uma propriedade
			printf ("\nErro ao alocar memoria para os dados.\n");					//	Do triangulo de pascal
			return (int)NULL;
		}
	}
	
	for (i = 0; i < num_linhas; i++) {
		pascal[i][0] = 1;				//	Todos os números da esquerda são iguais a 1. E são úteis para o cálculo dos próximos.
		for (j = 1; j < i + 1; j++) {							//	Propriedade do triangulo de pascal:
			pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];	//	Número atual = Numero de cima + Numero à sua diagonal superior esquerda
		}
	}
		
	
	printf ("\nO triangulo de pascal de [%u] linhas e:\n\n", num_linhas - 1);
	
	for (i = 0; i < num_linhas; i++) {	//	Imprimindo o triangulo
		for (j = 0; j <= i; j++) {
			printf ("%lu\t", pascal[i][j]);
		}
		printf ("\n");
	}
	
	for (i = 0; i < num_linhas; i++) {	/*	Liberando memória da HEAP 	*/
		free (pascal[i]);
	}
	free (pascal);
	
	return 0;
}

