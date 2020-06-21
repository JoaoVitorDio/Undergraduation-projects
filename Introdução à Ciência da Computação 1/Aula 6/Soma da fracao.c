#include <stdio.h>

/*	2) 	Faça um programa para calcular o valor da
		seguinte série:
		S = 1/1 + 3/2 + 5/3 + 7/4 + ... + 99/50	*/

int main () {

	int i;
	float num, soma;

	for (i = 1; i <= 50; i++) {
		num = ((i*2) - 1);
		soma = soma + (num/i);
	}
	printf ("%f", soma);
}
