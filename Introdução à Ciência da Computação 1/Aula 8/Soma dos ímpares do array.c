#include <stdio.h>
#include <conio.h>

/*	2) 	Desenvolva um programa que leia os valores de um
		vetor de 10 posições e calcule a soma dos valores
		armazenados em posições impares.	*/

int main () {

	int array[10], soma = 0;
	int count, printing;

    printf ("Digite 10 numeros, com enters entre eles.")
	for (count = 0; count < 10; count++)
		scanf ("%d", &array[count]);

	for (printing = 0; printing <10; printing = printing +2)
		soma = soma + array[printing];

	printf ("a soma dos numeros nas posicoes impares e: %d", soma);


	getch ();
	return 0;
}
