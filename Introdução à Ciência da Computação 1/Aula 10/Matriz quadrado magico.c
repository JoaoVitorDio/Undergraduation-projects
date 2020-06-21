#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

/*		Dizemos que uma matriz quadrada inteira é um
		quadrado mágico se a soma dos elementos de cada
		linha, a soma dos elementos de cada coluna e a
		soma dos elementos das diagonais principal e
		secundária são todas iguais.
		Dada uma matriz quadrada Anxn , verificar se A é um
		quadrado mágico.	*/

int main () {

	int soma, vlin, vcol, vdiag, lin, col, matriz[3][3] = {2, 7, 6, 9, 5, 1, 4, 3, 8};

	//Imprimindo a matriz que será avaliada
	printf ("A matriz:\n");
	for (lin=0;lin<3;lin++) {
		for (col=0;col<3;col++){
			printf ("%d ", matriz[lin][col]);
		}
		printf ("\n");
	}

	soma = matriz[0][0] + matriz [0][1] + matriz [0][2];

	for (lin=0;lin<3;lin++) {
		vlin = 0;
		for (col=0;col<3;col++){
			vlin = vlin + matriz[lin][col];
		}
		if (vlin != soma) {
			printf ("\nnao e quadrado magico");
			break;
		}
	}

	for (lin=0;lin<3;lin++) {
		vcol = 0;
		for (col=0;col<3;col++){
			vcol = vcol + matriz[col][lin];
		}
		if (vcol != soma) {
			printf ("\nnao e quadrado magico");
			break;
		}
	}

	vdiag = 0;
	for (lin=0;lin<3;lin++) {
		vdiag = vdiag + matriz[lin][lin];
	}
	if (vdiag != soma)	 {
		printf ("\nnao e quadrado magico");
	}

	// verificação da diagonal inversa.

	vdiag = 0;
    for (col=2;col>=0;col--) {
		vdiag = vdiag + matriz[2-col][col];
	}
	if (vdiag != soma)	 {
		printf ("\nnao e quadrado magico");
	}


	if (vlin==soma && vcol==soma && vdiag==soma)
	printf ("\ne quadrado magico");

	getch ();
	return 0;
}
