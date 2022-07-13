#include <stdio.h>

/*	4) 	Criar um programa em C que determina os
		n�meros de 1 a 5000 que s�o quadrados perfeitos
		(a raiz � um n�mero inteiro). N�o � permitido o uso
		de comandos do C para pot�ncia e raiz.	*/

int main () {

/* para esse exerc�cio, podemos resolv�-lo de forma "construtiva" e de forma "destrutiva", sendo a construtiva, aquela que parte dos n�meros inteiros
e forma o quadrado perfeito, e, a destrutiva, aquela que parte dos poss�veis quadrado perfeito e verifica sua "perfecto-quadradibilidade".
Na forma destrutiva, precisar�amos de um "for" contando os numeros de 1 a 5000 e outro "for" dentro de cada valor do "for" anterior para saber se o numero de
1 a 5000 possui algum i (entre 1 e 71) em que o resto do numero por i � i (if (num % i = i) ), o que seria uma conta absurdamente complicada e desnecess�ria. */

	int num, quadrado;
	
	printf ("os quadrados perfeitos de 1 a 5000 sao:\n");
	
	for (num=0; num < 71; num++) {
		quadrado = num*num;
		printf ("%d\n", quadrado);
	}
	
	return 0;
}
