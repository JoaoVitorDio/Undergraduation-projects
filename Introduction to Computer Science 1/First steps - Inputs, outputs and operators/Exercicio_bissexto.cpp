#include <stdio.h>
#include <math.h>

int main() {
	int ano;
	
	printf ("Digite o ano que deseja verificar se e bissexto:\n");
	scanf ("%d", &ano);
	
	if ((ano%400) == 0) {
		printf ("O ano %d e bissexto!", ano);}		
		else {			
			if ((ano%4)==0 && (ano%100)!=0) {
				printf ("O ano %d e bissexto!", ano);}
				else {
					printf ("O ano %d nao e bissexto.", ano);
				}
		}
	
	return 0;
}
