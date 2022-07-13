#include <stdio.h>
#include <conio.h>

/*	3) 	Faça um programa que leia um valor inteiro e
		calcule o seu fatorial.	*/

int main () {

	int i;
	double num;

	printf ("Digite um valor inteiro:");
	scanf ("%lf", &num);

	for (i = num - 1; i > 0; i--) {
		num = num*i;
	}

	printf ("O fatorial do numero digitado e: %.lf", num);

	getch();
	return 0;
}
