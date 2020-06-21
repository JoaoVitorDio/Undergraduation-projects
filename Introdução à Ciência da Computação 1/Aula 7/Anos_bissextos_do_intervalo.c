#include <stdio.h>
#include <math.h>
#include <conio.h>

/*	1) 	Ler um ano inicial e um ano final e imprimir
		todos os anos bissextos desse intervalo.
		Obs: um ano é bissexto se ele for divisível por
		400 ou se ele for divisível por 4 e não por
		100.	*/

int main () {

	int ano1, ano2, resto, bissexto, auxiliar;
	printf ("Digite o ano inicial e o ano final:");
	scanf ("%d %d", &ano1, &ano2);
	resto = (ano1 % 4);

	if (resto != 0) {
		ano1 = ano1 - resto + 4;
	}

	if ((ano1 % 100) == 0 && (ano1 % 400)!= 0) {
		ano1 = ano1 + 4;
	}

	while (ano1 <= ano2) {
		printf ("%d ", ano1);
		ano1 = ano1 + 4;
		
		if ((ano1 % 100) == 0) {
			ano1 = ano1 + 4;
		}
    }

	getch ();
	return 0;

}
