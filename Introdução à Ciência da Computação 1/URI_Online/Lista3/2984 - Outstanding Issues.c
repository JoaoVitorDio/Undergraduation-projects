#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

int main () {
	
	
	char vetor[100001];
	int i, j, k, count = 0, posicao;
	
	for (i = 0; i < 100001; i++) {
		
		vetor[i] = getchar();
		if (vetor[i] == '\n' || vetor[i] == '\0') {
	
			posicao = i;
			break;
		}
		
		else {
			if (vetor[i] == '(') {
				count++;
			}
			else if (vetor[i] == ')') {
				if (count > 0)
				count--;
			}
		}
		
	}
	
	if (count > 0)
	printf ("Ainda temos %d assunto(s) pendente(s)!\n", count);
	else 
	printf ("Partiu RU!\n");
	
	return 0;
}
