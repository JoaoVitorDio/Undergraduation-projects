#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h> 
//stdio.h = printf e scanf
//math.h = opera��es matem�ticas
//string.h = uso e declara��o de strings
//conio.h = comando getch

/*	Fa�a um programa em que v�rias notas ser�o digitadas e exiba, ao fim, a maior e a menor nota digitadas. 
	O programa termina se alguma nota < 0 for digitada	*/

int main () {
	
	int nota, notamaior, notamenor;
	printf ("Digite as notas.\n");
	scanf ("%d", &nota);
	
	notamaior = nota;
	notamenor = nota;
	
	while (nota >= 0) {
		if (nota > notamaior) {
			notamaior = nota;
		}
		if (nota < notamenor) {
			notamenor = nota;
		}
		scanf ("%d", &nota);
	}
	
	printf ("a maior nota e %d e a menor nota e %d.", notamaior, notamenor);

	return 0;
}
