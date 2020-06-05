#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*	Exercício 1 - aula 15 - Crie uma estrutura para armazenar dados de um carro, leia esses dados e imprima-os;
	Se o fabricante digitado for chevrolet, altere para "GM"	*/

struct carro {
	char fabricante[20];
	char modelo[20];
	unsigned int ano;
	char cor[10];
	float preco;
};

void registra_carro (struct carro *p);

int main () {
	
	struct carro c1;
	registra_carro (&c1);


	printf ("\n\nO fabricante e: %s \nO modelo e: %s  \nO ano e: %d  \nA cor e: %s  \nO preco e: %.2f", c1.fabricante, c1.modelo, c1.ano, c1.cor, c1.preco);
	
	return 0;
}

void registra_carro (struct carro *p) {
	
	printf ("Digite o fabricante do carro\n");
	gets(p->fabricante);
	
	printf ("Digite o modelo do carro\n");
	gets(p->modelo);

	printf ("Digite o ano do carro\n");
	scanf ("%d", &p->ano);
	fflush(stdin);
	
	printf ("Digite a cor do carro\n");
	gets(p->cor);

	printf ("Digite o preco do carro\n");
	scanf ("%f", &p->preco);
	
	if (p->ano < 2000)
	p->ano = 2000;
	if (stricmp(p->fabricante, "chevrolet") == 0)
	strcpy (p->fabricante, "GM");
}

