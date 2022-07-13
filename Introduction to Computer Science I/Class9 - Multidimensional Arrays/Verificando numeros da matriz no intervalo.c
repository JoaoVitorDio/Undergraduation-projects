#include <stdio.h>
#include <conio.h>

/*	2) 	Crie um programa que leia uma matriz 5x5 e troque
		os elementos da 3a linha pela 3a coluna e vice-versa.
		Obs: considere que a 3a linha e a 3a coluna da matriz
		referem-se ao índice 2.	*/

int main () {

	int col, lin, matriz[4][5], num1, num2, count=0;

	printf ("Digite os 20 numeros inteiros da matriz.");

	for (lin=0;lin<4;lin++) {
		for (col=0;col<5;col++){
			scanf ("%d", &matriz[lin][col]);
		}
	}

	printf ("Digite um intervalo, com o primeiro numero < segundo numero.");
	scanf ("%d %d", &num1, &num2);

	for (lin=0;lin<4;lin++) {
		for (col=0;col<5;col++){
			if (matriz[lin][col] >= num1 && matriz[lin][col] =< num2)
			count++;
		}
	}

	printf ("A quantia de numeros da matriz no intervalo digitado e: %d", count);

	getch ();
	return 0;
}
