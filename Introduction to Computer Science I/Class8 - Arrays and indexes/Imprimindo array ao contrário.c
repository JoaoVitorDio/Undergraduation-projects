#include <stdio.h>
#include <conio.h>

/*	1) 	Fa�a um programa em C que leia um conjunto de 10
		valores inteiros e escreva-os em ordem contr�ria.	*/

int main () {

	int array[10];
	int count, printing;

	for (count=0;count<10;count++)
		scanf ("%d", &array[count]);

	for (printing = 9;printing >=0;printing--)
		printf ("%d ", array[printing]);

	getch ();
	return 0;
}
