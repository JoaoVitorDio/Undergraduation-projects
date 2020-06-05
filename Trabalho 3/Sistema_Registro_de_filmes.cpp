/*	Exercício: Programa que cadastra e exibe filmes. Deve preencher os seguintes requisitos:
1)	Crie uma estrutura para armazenar dados sobre filmes
(título, gênero e ano).
2) Crie uma função que recebe um vetor de filmes, e lê as
informações de 5 filmes, preenchendo o vetor.
3) Crie uma função que receba o vetor de filmes e imprima as
informações dos filmes feitos 2001 e 2005.
4) Crie uma função que receba um vetor de filmes e imprima
as informações dos filmes de um determinado gênero,
também passado como argumento para a função. Ex:
“terror”
5) Crie uma função main que declara um vetor de 5 filmes e
usa as funções anteriores para preencher e imprimir as
informações do vetor.	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

struct filmes {
	char titulo[30];
	char genero[20];
	int ano;
	int catalogo;
	char disponivel;		/*	Para adicionar a funcionalidade de "disponibilidade" de um vetor, apenas criei uma variável controladora na struct, que 
								armazenará a informação de "cadastro" ou "inativo" */
};

int tamanho;		/*	O uso de variáveis globais é totalmente não-recomendado, mas nesse caso, em que o programa é pequeno e controlado, 
						com todas as funções bem definidas e o programador tem total controle do programa, foi utilizada para que não fosse
						necessário passar esse valor como argumento para todas as funções. Uma conveniência. Além de que, o seu valor não foi
						alterado em nenhuma função, apenas utilizado em comparações. */

void leitura (struct filmes *p);		
void filmes_intervalo (struct filmes *p);
void filmes_genero (struct filmes *p, char string[20]);
void imprimefilme (struct filmes filminho);
void limpatela();
void registrafilme (struct filmes *p);

int main () {
	
	char menu, loop = 1, string[20];			//	Armazenará informações uteis para usar como argumento às funções, como, genero dos filmes.
	struct filmes *vetor, *pointer;
	int numcatalogo, posicaoatual, controller;
	
	printf ("Digite a quantia de filmes que deseja registrar\n");	//	Alocação dinâmica de memória para que possamos armazenar quantos filmes quisermos.
	scanf ("%d", &tamanho);
	fflush(stdin);
	
	vetor = (struct filmes*) calloc (tamanho, sizeof(struct filmes));
	if (vetor == NULL) {
		printf ("\n\nErro: Memória insuficiente\n\n");
		return (int)NULL;
	}
	
	while(loop == 1) {		// 	Mantendo o menu em loop, para conseguir acessar todas as suas funções, sem necessariamente possuir um fluxo fixo de processos
		printf ("Qual acao deseja fazer?\n\n");
		
		printf ("Digite 1 para cadastrar todos os %d filmes.\nDigite 2 para filtrar os filmes cadastrados por ano.\n", tamanho);
		printf ("Digite 3 para digitar um genero de filmes e ver quais os filmes cadastrados que se enquadram.\n");
		printf ("Digite 4 para cadastrar apenas um filme em uma posicao especifica\n");
		printf ("Digite 5 para alterar os dados de um filme pelo numero de catalogo\n");
		printf ("Digite 6 para remover o cadastro de um filme, a partir do numero de\n catalogo. deixando o espaco livre para outro filme");
		printf ("Digite 9 para limpar a tela.\n");
		printf ("Digite 0 para sair do menu, e consequentemente fechar o programa.\n\n");
		
		scanf ("%c", &menu);
		fflush(stdin);
		
		switch (menu) {			//	Menu interativo. 
			case '0':
				loop = menu;
				break;
			case '1':
				leitura(&vetor[0]);
				break;
			case '2':
				filmes_intervalo(&vetor[0]);
				break;
			case '3':
				printf ("\nDigite por qual genero deseja filtrar os filmes.\n");
				gets (string);
				filmes_genero (&vetor[0], string);
				break;
			case '4':
				printf ("\nDigite em qual posicao de armazenamento deseja cadastrar um filme.\n");
				scanf ("%d", &posicaoatual);
				fflush (stdin);
				if (vetor[posicaoatual].disponivel == 1) {
					printf ("Essa posicao ja esta ocupada. Caso queira altera-la, digite 0;\nPara apenas retornar ao menu, digite 1.");
					scanf ("%d", &controller;)
					fflush(stdin);
					if (controller == 1) {
					system ("cls");
					printf ("Retornando ao menu...");
					Sleep (2000);
					break;
					}
					if (controller == 0)
					registrafilme(&vetor[posicaoatual]);
				}
				else {
				registrafilme(&vetor[posicaoatual]);
				}
				break;
			case '5':
				printf ("\nDigite o numero de catalogo do filme.\n");
				scanf ("%d", &numcatalogo);
				fflush (stdin);
				controller = verifica_catalogo(numcatalogo, pointer);
				if (controller == 1) {
					registrafilme(pointer);
				}
				else {
					printf ("\nNao ha nenhum filme cadastrado com esse numero de catalogo. Retornando ao menu...\n");
				}
				break;
			case '9':
				limpatela();
				break;
			default:
				printf ("\n\nO comando digitado e invalido. Retornando ao menu...");
				Sleep (2000);
				system("cls");
		}
	}
	
	free (vetor);	/* Liberando a memória alocada pelo vetor */
	return 0;
}

void registrafilme (struct filmes *p) {		//	Função de registrar um único filme
	
	system("cls");							//	Limpando a tela para que o programa fique mais apresentável

	printf ("\nDigite o titulo (nome) do filme:\n");	//	Solicitando o nome do filme
	gets(p->titulo);
	
	printf ("\nDigite o genero do filme:\n");			//	Solicitando o genero do filme
	gets (p->genero);
	
	printf ("\nDigite o ano de lancamento filme:\n");	//	Solicitando o ano do filme
	scanf ("%d", &p->ano);
	fflush(stdin);
	
	printf ("\nDigite o numero de catalogo do filme:\n");	//	Solicitando o numero de catalogo
	scanf ("%d", &p->catalogo);
	fflush(stdin);
	
	p->disponivel = 1;
}

void leitura (struct filmes *p) {		//	Função de cadastrar todos os filmes
	
	int count;
	
	for (count = 0; count < tamanho; count++) {
		printf ("\n\nRegistrando o %d filme\n", count+1);	//	Interação com o usuário
		registrafilme (&p[count]);
	}
}

void filmes_intervalo (struct filmes *p) {		//	Função de imprimir os filmes no intervalo digitado
	
	int count, ano1, ano2, aux;
	unsigned char controller = '0';

	
	system("cls");
	printf ("Digite duas datas no formado ano1 ano2\n");	//	Lendo um intervalo
	scanf ("%d %d", &ano1, &ano2);
	fflush(stdin);

	if (ano1 > ano2) {			//	Colocando o intervalo digitado em ordem crescente
		aux = ano1;
		ano1 = ano2;
		ano2 = aux;
	}
	
	for (count = 0; count < tamanho; count++) {			//	Filtrando os filmes no intervalo
		printf ("\n\n");
		if ((p[count].ano) >= ano1 && (p[count].ano)<=ano2) {
		controller = '1';
		imprimefilme (p[count]);
		}
	}
	if (controller == '0') {				// 	Exbindo mensagem de insucesso, caso não haja filmes registrados no intervalo
		printf ("Nao foi cadastrado nenhum filme neste intervalo.\n");
	}
}

void imprimefilme (struct filmes filminho) {		//	Função que imprime filmes únicos, recebendo o ponteiro para ele como argumento.
	
	printf ("O nome do filme e: %s\n", filminho.titulo);
	printf ("O genero do filme e: %s\n", filminho.genero);
	printf ("O ano do filme e: %d\n\n", filminho.ano);
}


void filmes_genero (struct filmes *p, char string[20]) {	//	Função que filtra os filmes por genero
	
	int count, controller = 0;
	
	printf ("Os filmes cadastrados, do genero \"%s\" sao:\n", string);		//	Interação
	
	for (count = 0; count < tamanho; count++) {		//	Filtro
		printf ("\n\n");
		if (stricmp(p[count].genero, string) == 0) {
		controller++;
		imprimefilme (p[count]);
		}
	}
	if (controller == 0)		//	Mensagem de erro, caso não haja nenhum filme do genero
	printf ("Nao foi cadastrado nenhum filme desse genero.\n\n");
}

void limpatela() {		//	Função para automatizar a limpeza de tela e deixar o programa mais modularizado e estético
	printf ("\n\n\nLimpando a tela...");
	Sleep (2000);
	system ("cls");
}
