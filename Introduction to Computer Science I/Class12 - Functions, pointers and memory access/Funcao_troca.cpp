/* Fa�a um programa que leia 2 valores inteiros e chame uma fun��o que receba estas 2 vari�veis e troque o seu conte�do, ou seja, esta rotina �
chamada passando duas vari�veis A e B por exemplo, e ap�s a execu��o da rotina A conter� o valor de B e B ter� o valor de A. */

#include <stdio.h>
#include <conio.h>

int funcaotroca (int *a, int *b);

int main () {
	
	int a, b;
	
	printf ("Digite o valor de A e B:\n");
	scanf ("%d %d", &a, &b);
	
	funcaotroca (&a, &b);
	
	printf ("O valor de A e: %d\nO valor de B e: %d", a, b);
	
	getch();
	return 0;
}

int funcaotroca (int *a, int *b) {
	
	int auxiliar;
	auxiliar = *a;
	*a = *b;
	*b = auxiliar;
}
