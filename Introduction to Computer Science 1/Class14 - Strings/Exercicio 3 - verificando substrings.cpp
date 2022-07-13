#include <stdio.h>
#include <conio.h>

/* Crie uma fun��o que recebe 2 strings (A e B) e retorna 1 se B � parte de A, sem usar fun��es da biblioteca string.h. A fun��o retorna 0 caso contr�rio. */

char substring(char* string1, char* string2);

int main () {
	
	char resultado, string1[50], string2[50];
	int i;
	
	printf ("Digite a primeira string:\n");
	for (i=0; i < 50; i++) {
		string1[i] = getchar();
		if (string1[i] == '\n') {
			string1[i] = '\0';
			break;
		}
	}
	
	printf ("Digite a segunda string:\n");
	for (i=0; i < 50; i++) {
		string2[i] = getchar();
		if (string2[i] == '\n') {
			string2[i] = '\0';
			break;
		}
	}
	
	resultado = substring(string1, string2);
	
	printf ("O resultado e: %c", resultado);
	
	return 0;
}

char substring(char* string1, char* string2) {
	
	char *inicial, result = '0';
	unsigned int tamanho1, tamanho2, count, i;
	
	//	Verificar o tamanho de cada string:
	for (count = 0; count < 50; count++) {
		if (string1[count] == '\0')
		break;
	}
	tamanho1 = count;
	
	for (count = 0; count < 50; count++) {
		if (string2[count] == '\0')
		break;
	}
	tamanho2 = count;
	
	//	Verificar se A cont�m B:
	
	if (tamanho2 < tamanho1) {
		
		for (count = 0; count < tamanho1; count++) {
			if (string1[count] == string2[0]) {
			inicial = &string1[count];
			result = '1';
			break;
			}
		}
		if (tamanho2 >= 2) {
			for (count = 0; count < tamanho2; count++) {
				if (*inicial != string2[count]) {
				result = '0';
				}
			inicial++;
			}
		}
	}
	return result;
}

