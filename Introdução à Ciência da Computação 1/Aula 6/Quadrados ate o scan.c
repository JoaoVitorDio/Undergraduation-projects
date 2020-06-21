#include <stdio.h>

/*	Imprime os quadrados perfeitos até o número lido	*/

void main() {

	int i, num, quadrado = 1;
	
	printf ("Digite um numero. \n\nO programa imprimira todos os quadrados perfeitos ate o valor digitado!\n");
	scanf ("%d", &num);
	
	for (i=1;; i++) {
	    quadrado=i*i;
	    
	    if (quadrado>num)
	        break;
	    printf("\nO numero %d e um quadrado perfeito.", quadrado);
	}
}
