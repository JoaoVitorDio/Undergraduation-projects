#include <stdio.h>
#include <conio.h>

/*	2)	Leia um n�mero positivo do usu�rio, ent�o,
		calcule e imprima a sequencia Fibonacci at� o
		primeiro n�mero superior ao n�mero lido.
		Exemplo: se o usu�rio informou o n�mero 30,
		a sequencia a ser impressa ser� 0 1 1 2 3 5 8
		13 21 34.	*/

int main () {

	int num, fibonacci = 0, fibonacci1 = 1;
	printf ("Digite o numero\n");
	scanf ("%d", &num);

	printf ("A sequencia de fibonacci ate o numero digitado e:\n");
	printf ("0, ");

	while (num > fibonacci || num > fibonacci1) {

	fibonacci1 = fibonacci + fibonacci1;
	fibonacci = fibonacci + fibonacci1;

	printf ("%d, ", fibonacci1);

        if (num > fibonacci) {
            printf ("%d, ", fibonacci);
        }
	}

	getch();
	return 0;
	}
