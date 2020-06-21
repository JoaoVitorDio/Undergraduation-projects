#include <stdio.h>
#include <math.h>

int main(){
	float distancia, gasto, consumo;
	
	printf ("Digite a distancia percorrida e o gasto total de combustivel no percurso:\n");
	scanf ("%f %f", &distancia, &gasto);
	
	consumo = (distancia/gasto);
	
	if (consumo < 8) {
	printf ("Venda o carro!");}
	else
		if ((consumo > 8) && (consumo < 12))	{
		printf ("Economico!");}
		else 
		printf ("Super economico!");

	return 0;
}
