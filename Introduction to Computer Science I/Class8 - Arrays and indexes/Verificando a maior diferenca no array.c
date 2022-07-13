#include <stdio.h>
#include <conio.h>

/*	4)	Ler um vetor A de 10 elementos inteiros.
		Determinar e imprimir a maior diferença entre dois
		elementos consecutivos desse vetor.	*/

int main () {

	int i, diferenca = 0, array[10];
	printf ("Digite 10 valores, cada um seguido de enter.");

	for(i = 0;i < 10;i++)
		scanf ("%d", &array[i]);

	for(i=1;i<10;i++) {
		if ( (array[i]-array[i-1]) > diferenca || (array[i-1]-array[i]) > diferenca) {
			diferenca = array[i]-array[i-1];
		// extraindo o módulo para não precisar identificar qual condição foi atendida
			if (diferenca < 0)
				diferenca = diferenca * (-1);
		}

	}

	printf ("A maior diferenca entre os consecutivos digitados e: %d", diferenca);

	getch ();
	return 0;
}
