#include <stdio.h>
#include <string.h>

//	Exercício 2 - Aula 2: Cálculo de vetor com structs	
int main () {
 
 	struct point { 
 		float x;
 		float y;
 		float z;
 	};
 	
 	struct point pointA;
	struct point pointB;
	struct point AB;
	
 	printf ("Digite a coordenada x do ponto 1:\n");
 	scanf ("%f", &pointA.x);	
 	
	printf ("Digite a coordenada y do ponto 1:\n");
 	scanf ("%f", &pointA.y);
 	
 	printf ("Digite a coordenada z do ponto 1:\n");
 	scanf ("%f", &pointA.z); 	
	 
	printf ("\n\nDigite a coordenada x do ponto 2:\n");
 	scanf ("%f", &pointB.x);	
 	
	printf ("Digite a coordenada y do ponto 2:\n");
 	scanf ("%f", &pointB.y);
 	
 	printf ("Digite a coordenada z do ponto 2:\n");
 	scanf ("%f", &pointB.z);
 	
 	AB.x = pointB.x - pointA.x;
 	AB.y = pointB.y - pointA.y;
 	AB.z = pointB.z - pointA.z;

	printf ("O vetor do ponto 1 ate o ponto 2 possui dimensoes:\nx = %.2f \ny = %.2f \nz = %.2f\n", AB.x, AB.y, AB.z);
   
   	return(0);
}
