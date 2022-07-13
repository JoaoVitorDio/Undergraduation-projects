#include <stdio.h>
#include <conio.h>

/*	3) 	Faça um programa que leia 2 vetores de 5
		elementos inteiros e que calcule o vetor soma.	*/

int main () {

	int array1[5], array2[5], soma[5], count1, count2;

	printf ("Digite os valores do primeiro vetor:");

	for (count1=0;count1<5;count1++)
	scanf ("%d", &array1[count1]);

	printf ("Digite os valores do segundo vetor:");

	for (count2=0;count2<5;count2++)
	scanf ("%d", &array2[count2]);

	//Conseguindo a soma:

	printf ("O vetor soma e:\n");

	for (count1=0;count1<5;count1++) {
	soma[count1] = array1[count1] + array2[count1];
	printf ("%d ", soma[count1]);
	}

	getch ();
	return 0;
}
