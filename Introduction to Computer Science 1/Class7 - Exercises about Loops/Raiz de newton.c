#include <stdio.h>
#include <conio.h>

/*	6) 	Criar uma fun��o que receba como
		argumento um n�mero real e um n�mero
		inteiro e retorne a raiz quadrada do n�mero
		real atrav�s de Newton:
		R1 = E/2
		Rn+1 = (Rn + (E/Rn))/2
		para E = entrada, R = raiz quadrada
		e n = n�mero de itera��es	*/

int main () {

	int count, i;
	float num;
	double raiz;

	printf ("Digite um numero real que deseja descobrir a raiz e o numero de interacoes\n\n");
	scanf ("%f %d", &num, &count);

	for (i=1;i <= count;i++) {

		if (i <= 1) {
			raiz = num/2;
		}
		else
			raiz = (raiz + (num/raiz))/2;
	}

	printf ("\na raiz do numero %f e: %lf", num, raiz);

	getch();
	return 0;
}
