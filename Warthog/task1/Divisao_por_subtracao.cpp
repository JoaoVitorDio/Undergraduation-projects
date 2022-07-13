/*	Implemente um programa em C que leia dois números A e B e imprima em linhas separadas, o resultado da divisão a/b e seu resto, 
utilizando apenas a operação de SUBTRAÇÃO para isso.	*/

#include <stdio.h>

int main() {
	
	int numerador, denominador, quociente = 0, resto;
	
	printf ("Digite o numerador:");
	scanf ("%d", &numerador);
		
	printf ("Digite o denominador:");
	scanf ("%d", &denominador);
	
	if (denominador == 0) {
	printf ("\n\nEis o decimo primeiro mandamento de Moises: Jamais dividiras por 0!\nBixo burro...");
	return 0;
	}

	for (resto = numerador; resto >= denominador;) {	//	Quociente = Quantas subtrações sucessivas fomos capazes de fazer, até que 
		resto -= denominador;							//	o resto seja menor que o num
		quociente++;
	}
	
	printf ("\nO resultado da divisao de %d por %d possui:\n \nQuociente: %d\nResto:%d\n\n", numerador, denominador, quociente, resto);
	
	return 0;	
}
