//	Protótipo de calculadora

#include <stdio.h>

int main () {
	
	float valor1 = 1, valor2, result;
	char operador;

	printf ("Digite uma operacao aritmetica:\n");
	
	scanf ("%f%c%f", &valor1, &operador, &valor2);

	switch (operador) {
		case '+':
			result = valor1 + valor2;
			break;
		
		case '-':
			result = valor1 - valor2;
			break;
		case '/':
			result = valor1 / valor2;
			break;
		case '*':
			result = valor1 * valor2;
			break;
			
		default:
			printf ("Operacao invalida\n");
			break;
	}
	
	printf ("\nO resultado da operacao e: %.2f", result);
	
	return 0;
}
