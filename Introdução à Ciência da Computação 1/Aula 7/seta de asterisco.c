#include <stdio.h>
#include <conio.h>

/*	5) 	Crie uma função que recebe um inteiro e
		exibe uma “seta”. Obs: A linha central da
		seta deverá ter tamanho n.
		Ex. para n = 3: 
		*
		* *
		* * *
		* *
		*			*/

int main () {

	int seta, linha, coluna, coluna2;

	printf ("Digite a linha central da seta:");
	scanf ("%d", &seta);

	for (linha = 1;linha<seta;linha++) {

		printf ("\n");
		for (coluna = 1;coluna<=linha;coluna++)
			printf ("* ");
	}

	for (seta - 1;seta > 0;seta--) {
		coluna2 = seta;
		printf ("\n");
		for (;coluna2 > 0;coluna2--)
			printf ("* ");

	}

	getch();
	return 0;
}
