#include <stdio.h>
#include <math.h>

/*	Fa�a um programa que calcule a m�dia aritm�tica entre dois n�meros 	*/

int main() {
	
	int num1, num2;
	float media;
	
	printf("Digite 2 numeros: \n");
	scanf("%d %d", &num1, &num2);
	
	media = (num1+num2)/2.0;
	
	printf("\n Media: %f", media);
	
	return 0;
	
}
