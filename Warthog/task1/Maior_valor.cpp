/* Implemente um programa em C que leia na entrada padr�o de texto (teclado) tr�s n�meros inteiros a, b e c, um em cada linha.
Em seguida,imprima na tela o valor correspondente ao maior desses n�meros	*/

#include <stdio.h>

int main () {
	
	/*	Um saco fazer isso aqui por verifica��o manual... Vetor >>>>>>> */
	
	int a, b, c;
	
	//	Lendo os tr�s valores...
	printf ("Digite o primeiro valor:\n");
	scanf ("%d", &a);
	
	printf ("Digite o segundo valor:\n");
	scanf ("%d", &b);
	
	printf ("Digite o terceiro valor:\n");
	scanf ("%d", &c);
	
	if (a > b) {
		if (a > c) 
		printf ("O maior valor e: %d", a);
		else 
		printf ("O maior valor e: %d", c);
	}
	else {
		if (c > b)
		printf ("O maior valor e: %d", c);
		else 
		printf ("O maior valor e: %d", b);
	}
	
	return 0;
}
