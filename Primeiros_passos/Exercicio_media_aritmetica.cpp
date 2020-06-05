#include <stdio.h>
#include <math.h>

/*	Faça um programa que calcule a média aritmética entre dois números 	*/

int main() {
	
	int num1, num2;
	float media;
	
	printf("Digite 2 numeros: \n");
	scanf("%d %d", &num1, &num2);
	
	media = (num1+num2)/2.0;
	
	printf("\n Media: %f", media);
	
	return 0;
	
}
