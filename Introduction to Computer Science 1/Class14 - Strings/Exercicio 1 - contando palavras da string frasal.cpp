#include <stdio.h>
#include <conio.h>

/*	Faça um exercicio que conta as palavras de uma string digitada	*/

int main () {
	
	int count, numpalavras = 1;
	char frase[51];
	printf ("Digite uma frase\n");
	gets(frase);
	
	for (count = 0; count < 51; count++) {
		if (frase[count] == '\0')
		break;
		
		if (frase[count] == ' ')
		numpalavras++;
	}
	
	printf ("O numero de palavras digitadas foi: %d", numpalavras);
	
	getch ();
	return 0;
}
