#include <stdio.h>
#include <conio.h>

/*	Faça uma função que receba uma string e um caractere qualquer. A função retorna a mesma string retirando todas as ocorrências do caractere.
Exemplo: Seja a string "arvore" e o caractere 'r', então a string ficará "avoe". */

void modifica_string(char* v, char caractere);

int main() {
	
	int count;
	char string[50], caractere;
	
	printf ("Digite uma string: \n");
	for (count = 0; count < 50; count++) {
		string[count] = getche();
		if (string[count] == 13) {
			string[count] = '\0';
			printf ("\n");
		break;
		}
	}
	count --;
	
	printf ("Digite um caractere:\n");
	caractere = getchar();
	
	modifica_string (&string[0], caractere);
	
	printf ("\nA string sem o caractere %c e: %s", caractere, string);
		
	return 0;
}

void modifica_string(char* v, char caractere) {

	int count, tamanho, i;
	
	// 	verificar tamanho da string
	for (count = 0; count < 50; count++) {
		if (v[count] == '\0')
		break;
	}
	tamanho = count;
	
	for (count = 0; count < tamanho; count++) {
		if (v[count] == caractere) {
			for (i = count; i < tamanho; i++) {
				v[i] = v[i+1];
			}
			tamanho -= 1;
		}
	}
	
}

