#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

/*	Crie um programa que leia um vetor de 10 inteiros,
	ordene e imprima os valores lidos.	*/

int main () {

	int array[10], aux, count, i;

	for (count = 0;count<10;count++) {
		scanf ("%d", &array[count]);
	}

	/* agora precisamos ordenar os numeros no array em ordem crescente... para isso, utilizaremos a seguinte estrat�gia:
	Come�aremos a leitura do array com o primeiro for, e com o segundo, comparamos a posi��o atual com todas as outras.
	Se um n�mero � direita do lido for maior que ele, eles trocam de posi��o.
	Em suma, passamos os numeros maiores para a direita at� que n�o haja mais nenhum n�mero menor que ele � sua direita. */

	for (count = 0;count<10;count++) {
		for (i = 0;i<10;i++){
			if (array[count]<array[i]) {
				aux=array[i];
				array[i]=array[count];
				array[count]=aux;
			}
		}
	}

	for (count = 0;count<10;count++)
		printf ("%d ", array[count]);

	getch ();
	return 0;
}
