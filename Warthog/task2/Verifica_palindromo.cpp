#include <stdio.h>
#include <conio.h>
#include <string.h>

/*	Verifique se a palavra digitada � pal�ndroma */

int main() {
	
	char string[50], resultado[4] = "Sim";
	int i, j;
	
	printf ("Digite uma string (conjunto de caracteres).\n");
	gets(string);
	
	j = strlen(string);
	j--;
	
	//	Estrat�gia:	Comparar a ultima letra com a primeira, a penultima com a segunda e assim sucessivamente, at� que cheguemos na metade da palavra.
	for (i = 0; i < j; i++) {
		if (string[i] != string[j]) {
			strcpy (resultado, "Nao");
		}
		j--;
	}
	
	printf ("%s", resultado);
	
	return 0;
}
