/* Escreva uma função que dado um número real passado como parâmetro, retorne a parte inteira e a parte fracionária deste número. */

#include <stdio.h>
#include <conio.h>
#include <math.h>

void funcaosepara (float *frac, int *inteiro);

int main () {
	
	float partefrac;
	int parteinteira;
	
	printf ("Digite um numero real: \n");
	scanf ("%f", &partefrac);
	
	funcaosepara (&partefrac, &parteinteira);
	
	printf ("A parte inteira do numero e: %d, e a parte fracionaria e: %f", parteinteira, partefrac);
	
	getch ();
	return 0;
}

void funcaosepara (float *frac, int *inteiro) {
	
	*inteiro = trunc (*frac);
	*frac = *frac - *inteiro;
	
}

