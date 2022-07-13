/*	Implemente um programa em C que leia dois n�meros A e B e imprima em linhas separadas, o resultado da divis�o a/b e seu resto, 
utilizando apenas a opera��o de SUBTRA��O para isso.	*/

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

	for (resto = numerador; resto >= denominador;) {	//	Quociente = Quantas subtra��es sucessivas fomos capazes de fazer, at� que 
		resto -= denominador;							//	o resto seja menor que o num
		quociente++;
	}
	
	printf ("\nO resultado da divisao de %d por %d possui:\n \nQuociente: %d\nResto:%d\n\n", numerador, denominador, quociente, resto);
	
	return 0;	
}
