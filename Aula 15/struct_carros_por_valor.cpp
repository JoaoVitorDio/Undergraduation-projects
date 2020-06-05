#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*	Exercício 1 - aula 15 - struct de um carro 	*/

struct carro {
	char fabricante[20];
	char modelo[20];
	unsigned int ano;
	char cor[10];
	float preco;
};

struct carro registra_carro (struct carro carrito);

int main () {
	
	struct carro c1;
	c1 = registra_carro (c1);


	printf ("\n\nO fabricante e: %s \nO modelo e: %s  \nO ano e: %d  \nA cor e: %s  \nO preco e: %.2f", c1.fabricante, c1.modelo, c1.ano, c1.cor, c1.preco);
	
	return 0;
}

struct carro registra_carro (struct carro carrito) {
	
	printf ("Digite o fabricante do carro\n");
	gets(carrito.fabricante);
	
	printf ("Digite o modelo do carro\n");
	gets(carrito.modelo);

	printf ("Digite o ano do carro\n");
	scanf ("%d", &carrito.ano);
	fflush(stdin);
	
	printf ("Digite a cor do carro\n");
	gets(carrito.cor);

	printf ("Digite o preco do carro\n");
	scanf ("%f",&carrito.preco);
	
	return carrito;
}

