#include <stdio.h>
#include <string.h>

//	Exercício 3 - Aula 2: Função que calcule o fatorial do número recebido como argumento.

int fat (int number);

int main () {
 
 	unsigned int numero, resultado;
 	
 	printf ("Digite um numero para o calculo do fatorial:\n");
 	scanf ("%d", &numero);
 	
 	resultado = fat (numero);
 	
 	printf ("O fatorial de %d e: %d", numero, resultado);
   
   	return(0);
}

int fat (int number) {
	
	unsigned int i;
	
	for (i = (number - 1); i > 0; i--) {
	number = number*i;
	}
	
	return number;
}
