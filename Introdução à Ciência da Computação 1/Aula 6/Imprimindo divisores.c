#include <stdio.h>

/*	Crie um programa que receba um valor positivo
	inteiro e imprime os divisores desse valor.	*/

int main () {

	int num, divisor, i;

	scanf ("%d", &num);

	printf ("Os divisores, em ordem crescente, sao: \n");

	for (i = 1; i <= num; i++) {
	    divisor = i;
		if ((num%divisor) == 00) {
			printf ("%d\n", divisor);
		}

	}
}
