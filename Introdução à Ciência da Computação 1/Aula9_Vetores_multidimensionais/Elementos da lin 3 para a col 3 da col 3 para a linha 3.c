#include <stdio.h>
#include <conio.h>

	/*	3)	Crie e leia os valores de uma matriz 4 x 5 inteiros.
			Leia 2 inteiros (A e B), sendo que A deve ser menor
			do que B. Contar quantos valores da matriz estão
			dentro do intervalo [A, B].
			Obs: Os valores A e B estão incluídos nesse intervalo.	*/

int main () {

	int col, lin, matriz[5][5], backup[5];

	for (lin=0;lin<5;lin++) {
		for (col=0;col<5;col++){
			printf ("Digite o elemento [%d] [%d] da matriz.", lin, col);
			scanf ("%d", &matriz[lin][col]);
		}
	}

	// Passando os valores da linha 3 para o array de backup
	for (lin=2;lin==2;lin++) {
		for (col=0;col<5;col++)
			backup[col] = matriz[2][col];
	}

	// Passando os valores da coluna 3 para a linha 3

	for (col=2;col==2;col++) {
		for (lin=0;lin<5;lin++) {
			matriz[2][lin] = matriz[lin][2];
		}
	}

	// Passando os valores do backup para a coluna 3

	for (col=2;col==2;col++) {
		for (lin=0;lin<5;lin++) {
			matriz[lin][2] = backup[lin];
		}
	}

	// Imprimindo a matriz para conferir

	for (lin=0;lin<5;lin++) {
		for (col=0;col<5;col++){
			printf ("%d ", matriz[lin][col]);
			if (col==4)
			printf ("\n");
		}
	}

	getch ();
	return 0;
}
