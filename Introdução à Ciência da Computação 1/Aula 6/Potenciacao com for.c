#include <stdio.h>
#include <conio.h>

/*	Ler x e y e calcular xy sem usar funções de
	potência da linguagem C.	*/

int main () {

	int x, y, result;
	int i;

	printf ("Digite a base e entao, digite o expoente.\n")
	scanf ("%d %d", &x, &y);
	result = x;

	if (y == 0) {
		result = 1;
	}
	else {
		for (i=2; i <= y; i++) {
			result = (result*x);
		}
	}

	printf ("%d elevado a %d e: %d", x, y, result);
}
