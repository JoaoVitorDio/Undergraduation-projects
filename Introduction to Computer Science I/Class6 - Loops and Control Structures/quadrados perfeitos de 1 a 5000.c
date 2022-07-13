#include <stdio.h>

/*	4) 	Criar um programa em C que determina os
		números de 1 a 5000 que são quadrados perfeitos
		(a raiz é um número inteiro). Não é permitido o uso
		de comandos do C para potência e raiz.	*/

int main () {

/* para esse exercício, podemos resolvê-lo de forma "construtiva" e de forma "destrutiva", sendo a construtiva, aquela que parte dos números inteiros
e forma o quadrado perfeito, e, a destrutiva, aquela que parte dos possíveis quadrado perfeito e verifica sua "perfecto-quadradibilidade".
Na forma destrutiva, precisaríamos de um "for" contando os numeros de 1 a 5000 e outro "for" dentro de cada valor do "for" anterior para saber se o numero de
1 a 5000 possui algum i (entre 1 e 71) em que o resto do numero por i é i (if (num % i = i) ), o que seria uma conta absurdamente complicada e desnecessária. */

	int num, quadrado;
	
	printf ("os quadrados perfeitos de 1 a 5000 sao:\n");
	
	for (num=0; num < 71; num++) {
		quadrado = num*num;
		printf ("%d\n", quadrado);
	}
	
	return 0;
}
