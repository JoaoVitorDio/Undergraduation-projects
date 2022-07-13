#include <stdio.h>

int main () {

	int rounds, position, i;
	double fibo, aux, prox;

	scanf ("%d", &rounds);

	while (rounds>0) {

		scanf ("%d", &position);
		i = position;
		fibo=0;
		aux=1;

			while (i>0) {

				prox = fibo + aux;
				fibo = aux;
				aux = prox;

				i--;
			}

		printf ("Fib(%d) = %.f\n", position, fibo);
		rounds --;
	}

	return 0;
}

