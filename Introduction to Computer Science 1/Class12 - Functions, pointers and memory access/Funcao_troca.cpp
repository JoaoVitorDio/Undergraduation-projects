/* Faça um programa que leia 2 valores inteiros e chame uma função que receba estas 2 variáveis e troque o seu conteúdo, ou seja, esta rotina é
chamada passando duas variáveis A e B por exemplo, e após a execução da rotina A conterá o valor de B e B terá o valor de A. */

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
