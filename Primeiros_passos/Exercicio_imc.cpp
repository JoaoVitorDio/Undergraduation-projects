#include <stdio.h>
#include <math.h>

/*	Faça um programa que calcule o IMC de uma pessoa.	*/

int main (){
	
	float peso, alt, imc;
	
	printf ("Digite o seu peso em kg:\n");
	scanf ("%f", &peso);
	
	printf ("Digite a sua altura em metros:\n");
	scanf ("%f", &alt);
	
	imc = (peso/(pow(alt, 2)));

	if (imc<18.5) {
		printf ("abaixo do peso");
	}
		else if (imc<24.9) {
			printf ("Saudavel");
		}	
			else if (imc<29.9){
				printf ("Peso em excesso");
			}
				else  if (imc<34.9){
					printf ("Obesidade grau I");
				}
					else if (imc<39.9){
						printf ("Obesidade grau II");
					}
						else 
						printf ("Obesidade grau III");
		
	return 0;
}
