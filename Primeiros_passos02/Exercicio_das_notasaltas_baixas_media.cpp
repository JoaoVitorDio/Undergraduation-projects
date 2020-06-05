#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h> 
//stdio.h = printf e scanf
//math.h = operações matemáticas
//string.h = uso e declaração de strings
//conio.h = comando getch

/*	Faça um programa que leia as notas dos alunos (até que uma nota menor que 0 seja digitada), e ao fim, exiba
	O número de notas altas, o num de notas baixas, qual a porcentagem de alunos que obtiveram notas altas e a média final da sala	*/

int main () {
	
	float nota, soma = 0, media, percentual;
	float notabaixa = 0, notaalta = 0;
	
	printf ("Digite a nota dos alunos.\n");
	scanf ("%f", &nota);
	
	while (nota >= 0) {
		if (nota < 5) {
			notabaixa = notabaixa + 1;
		}
		else {
			notaalta = notaalta + 1;
		}
		soma = soma + nota;
		scanf ("%f", &nota);	
	}
	
	percentual = ((notaalta/(notaalta+notabaixa))*100);
	media = soma/(notaalta+notabaixa);
	
	printf ("%.f alunos obtiveram notas baixas, %.f obtiveram notas altas, \na media geral e %.2f e, \no percentual de alunos que obtiveram nota maior ou igual a 5 foi de %.4f%%", notabaixa, notaalta, media, percentual);
	
	getch ();
	return 0;
}
