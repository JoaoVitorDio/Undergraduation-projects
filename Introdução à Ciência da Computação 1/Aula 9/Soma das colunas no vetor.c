#include <Stdio.h>
#include <conio.h>

/*	1) 	Faça um programa que leia uma matriz 4x5 de
		inteiros e calcule a soma dos elementos de cada
		coluna, armazenando o resultado da soma, em um
		vetor de 5 elementos.	*/

int main () {

	int lin, col, mat[4][5], vetor[5] = {0,0,0,0,0};

	printf ("Digite os valores da matriz, com enters. (a matriz possui 4 linhas  e 5 colunas)");

	for (lin=0;lin<4;lin++) {
		for (col=0;col<5;col++) {
			scanf ("%d", &mat[lin][col]);
		}
	}

	for (col=0;col<5;col++) {
		for (lin=0;lin<4;lin++){
			vetor[col] = vetor[col] + mat[lin][col];
		}
	}

	for (col=0;col<5;col++) {
		printf ("%d ", vetor[col]);
	}

	getch();
	return 0;
}
