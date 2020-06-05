/*	Criar uma estrutura carro com os dados: modelo, cor, preço. Declarar um vetor com 5
elementos do tipo carro. Armazenar esse vetor em um arquivo de dados binários.
Abra o arquivo criado anteriormente e imprime as informações dos carros que custem mais de
R$20.000,00	*/

#include <stdio.h>

typedef struct carros {
	char modelo[20];
	char cor[20];
	float preco;
} carro;

int main () {
	
	int i;
	carro carrinhos1[5], carrinhos2[5];
	
	FILE *arquivo;
	
	for (i = 0; i < 5; i++) {
		printf ("\n\nDigite o modelo do carro:\n");
		gets(carrinhos1[i].modelo);
		printf ("\nDigite a cor do carro:\n");
		gets (carrinhos1[i].cor);
		printf ("\nDigite o preco do carro:\n");
		scanf ("%f", &carrinhos1[i].preco);
		fflush (stdin);
	}
	
	arquivo = fopen("teste.txt", "wb+");
	if (arquivo == NULL)
	printf ("Erro ao abrir o arquivo\n\n");
	
	fseek (arquivo, 0, SEEK_SET);
	
	fwrite (carrinhos1, sizeof(carro), 5, arquivo);
	fclose (arquivo);
	
	arquivo = fopen("teste.txt", "ab+");
	fseek (arquivo, 0, SEEK_SET);
	
	fread (carrinhos2, sizeof(carro), 5, arquivo);
	
	for (i = 0; i < 5; i++) {
		if (carrinhos2[i].preco > 20000) {
		
		printf ("\n\n As informacoes sobre o carro [%d] sao:\n\n", i+1);
		printf ("Modelo do carro: %s\n", carrinhos2[i].modelo);
		printf ("Cor do carro: %s\n", carrinhos2[i].cor);
		printf ("Preco do carro: %f\n", carrinhos2[i].preco);
		}
	}

	fclose (arquivo);
	return 0;
}
