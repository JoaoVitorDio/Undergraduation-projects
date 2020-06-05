#include <stdlib.h>
#include <stdio.h>

	/* Desenvolva uma função que receba 2 matrizes (A e B) e as dimensões dessa	matrizes, aloque e retorne a matriz soma. 
	Crie também o programa principal, que lê as dimensões das matrizes A e B, use a função vista anteriormente para alocá-las, chame a
	função acima para obter a matriz soma, imprima a matriz soma e libere a memória de todas as matrizes. */

int** alocar_matriz (int m, int n);
int** somar_matriz (int m, int n, int** matriza, int** matrizb); 
int* libera_memoria (int m, int n, int** matriz);


int main () { 
	
	int lin, col, i, j, **matriza, **matrizb, **matrizsoma;
	
	// scanear as dimensões das matrizes
	printf ("Digite a dimensao das matrizes no formato ""linhasxcolunas""\n");
	scanf ("%dx%d", &lin, &col);
	
	// chamar a função para alocar a matriz
	matriza = alocar_matriz (lin, col);
	
	// Preencher a matriz A:
	printf ("\n");
	for (i = 0; i < lin; i++) {
		for (j = 0; j < col; j++) {
			printf ("Digite o numero da posicao [%d][%d] da primeira matriz\n", i+1, j+1);
			scanf ("%d", &matriza[i][j]);
		}
	}
	
	matrizb = alocar_matriz (lin, col);
	
	// Preencher a matriz B:
	printf ("\n\n");
	for (i = 0; i < lin; i++) {
		for (j = 0; j < col; j++) {
			printf ("Digite o numero da posicao [%d][%d] da segunda matriz\n", i+1, j+1);
			scanf ("%d", &matrizb[i][j]);
		}
	}
	
	matrizsoma = somar_matriz(lin, col, matriza, matrizb);
	
	// 	Imprimindo a matriz soma
	printf ("\n\nA matriz soma e: \n\n");
	for (i = 0; i < lin; i++) {
		for	(j = 0; j < col; j++) {
		printf ("[%d]", matrizsoma[i][j]);
		}
	printf ("\n");
	}

	// 	limpando todas:
	libera_memoria (lin, col, matriza);
	libera_memoria (lin, col, matrizb);
	libera_memoria (lin, col, matrizsoma);
	
	return 0;
}	

int** alocar_matriz (int m, int n) {
	
	int **v, i;
	
	// conferindo os parametros (ver se é realmente uma matriz)
	if (m < 1 || n <1) {
		printf ("Erro: Parametros invalidos.");
		return NULL;
	}
	
	v = (int**) calloc(m, sizeof(int*));
	
		// Mensagem de erro caso não haja memória o suficiente para criar um vetor de ponteiros
		if (v == NULL) {
			printf ("Erro: Memoria insuficiente.");
			return NULL;
		}
	
	// 	Alocando vetores para cada linha (ponteiro) do ponteiro de ponteiros (vetor de ponteiros)
	for (i = 0; i < m; i++) {
		v[i] = (int *) calloc (n, sizeof(int));
		
		//	Mensagem de erro caso não haja memória o suficiente para criar um vetor para cada linha
		if (v[i] == NULL) {
			printf ("Erro: Memoria insuficiente.");
			return NULL;
		}
	}
	return v;
}

int** somar_matriz(int m, int n, int** matriza, int** matrizb) {
	int i, j, **v;
	
	v = alocar_matriz (m, n);
	
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			v[i][j] = matriza[i][j] + matrizb[i][j];
		}
	}
	return v;
}

int* libera_memoria(int m, int n, int **matriz) {
	
	int i;
	
	//	Verificando parametros
	if (matriz == NULL) 
		return NULL;
	
	if (m < 1 || n < 1) {
		printf ("Erro: Parametros invalidos.");
		return NULL;
	}
	
	for (i = 0; i < m; i++) {
		free (matriz[i]);
	}
	free (matriz);
	return NULL;
}
