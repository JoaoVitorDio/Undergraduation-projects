/* Implemente um programa em C que leia na entrada padrão de texto (teclado) três números inteiros a, b e c, um em cada linha.
Em seguida,imprima na tela o valor correspondente ao maior desses números	*/

#include <stdio.h>

int main () {
	
	/*	Um saco fazer isso aqui por verificação manual... Vetor >>>>>>> */
	
	int a, b, c;
	
	//	Lendo os três valores...
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
