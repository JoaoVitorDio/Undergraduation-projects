/*	Exerc�cio: Programa que cadastra e exibe filmes. Deve preencher os seguintes requisitos:
1)	Crie uma estrutura para armazenar dados sobre filmes
(t�tulo, g�nero e ano).
2) Crie uma fun��o que recebe um vetor de filmes, e l� as
informa��es de 5 filmes, preenchendo o vetor.
3) Crie uma fun��o que receba o vetor de filmes e imprima as
informa��es dos filmes feitos 2001 e 2005.
4) Crie uma fun��o que receba um vetor de filmes e imprima
as informa��es dos filmes de um determinado g�nero,
tamb�m passado como argumento para a fun��o. Ex:
�terror�
5) Crie uma fun��o main que declara um vetor de 5 filmes e
usa as fun��es anteriores para preencher e imprimir as
informa��es do vetor.	*/

/*	Atualize o programa com as funcoes de remover cadastro, num_de_catalogo, e disponibilidade do filme	*/

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
	char disponivel;		/*	Para adicionar a funcionalidade de "disponibilidade" de um vetor, apenas criei uma vari�vel controladora na struct, que 
								armazenar� a informa��o de "cadastro" ou "inativo" */
};

int tamanho;		/*	O uso de vari�veis globais � totalmente n�o-recomendado, mas nesse caso, em que o programa � pequeno e controlado, 
						com todas as fun��es bem definidas e o programador tem total controle do programa, foi utilizada para que n�o fosse
						necess�rio passar esse valor como argumento para todas as fun��es. Uma conveni�ncia. Al�m de que, o seu valor n�o foi
						alterado em nenhuma fun��o, apenas utilizado em compara��es. */

void leitura (struct filmes *p);		
void filmes_intervalo (struct filmes *p);
void filmes_genero (struct filmes *p, char string[20]);
void imprimefilme (struct filmes filminho);
void limpatela();
void registrafilme (struct filmes *p);
int verifica_catalogo (int num, int *p, struct filmes *vetormain);
void apaga_registro (struct filmes *p);

int main () {
	
	char menu, loop = 1, string[20];			//	Armazenar� informa��es uteis para usar como argumento �s fun��es, como, genero dos filmes.
	struct filmes *vetor, *pointer;
	int numcatalogo, posicaoatual, controller, count;
	
	printf ("Digite a quantia de filmes que deseja registrar\n");	//	Aloca��o din�mica de mem�ria para que possamos armazenar quantos filmes quisermos.
	scanf ("%d", &tamanho);
	fflush(stdin);
	
	vetor = (struct filmes*) calloc (tamanho, sizeof(struct filmes));
	if (vetor == NULL) {
		printf ("\n\nErro: Mem�ria insuficiente\n\n");
		return (int)NULL;
	}
	
	while(loop == 1) {		// 	Mantendo o menu em loop, para conseguir acessar todas as suas fun��es, sem necessariamente possuir um fluxo fixo de processos
		printf ("Qual acao deseja fazer?\n\n");
		
		printf ("Digite 1 para cadastrar todos os %d filmes. \n(Essa opcao apagara todos os filmes ja cadastrados, caso haja algum.)\n", tamanho);
		printf ("Digite 2 para filtrar os filmes cadastrados por ano.\n");
		printf ("Digite 3 para digitar um genero de filmes e ver quais os filmes cadastrados que se enquadram.\n");
		printf ("Digite 4 para cadastrar apenas um filme em uma posicao especifica\n");
		printf ("Digite 5 para alterar os dados de um filme pelo numero de catalogo\n");
		printf ("Digite 6 para remover o cadastro de um filme, a partir do numero de\ncatalogo, deixando o espaco livre para outro filme\n");
		printf ("Digite 7 para visualizar todos os filmes cadastrados.\n");
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
				if (vetor[posicaoatual].disponivel == '1') {
					printf ("Essa posicao ja esta ocupada. Caso queira altera-la, digite 0;\nPara apenas retornar ao menu, digite 1.\n");
					scanf ("%d", &controller);
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
				controller = verifica_catalogo(numcatalogo, &posicaoatual, &vetor[0]);
				if (controller == 1) {
					registrafilme(&vetor[posicaoatual]);
				}
				else {
					printf ("\nNao ha nenhum filme cadastrado com esse numero de catalogo. \nRetornando ao menu...\n");
				}
				break;
			case '6':
				printf ("Digite o numero de catalogo do filme que deseja remover.\n");
				scanf ("%d", &numcatalogo);
				fflush (stdin);
				controller = verifica_catalogo(numcatalogo, &posicaoatual, &vetor[0]);
				if (controller == 1) {
					apaga_registro (&vetor[posicaoatual]);
					printf ("\nO filme de antigo numero de catalogo = %d foi removido com sucesso! ;)\n\n", numcatalogo);
				}
				if (controller == 0) {
					printf ("Nao ha nenhum filme com esse numero de catalogo para remover.\n\n");
					Sleep (2000);
					limpatela();
				}
				break;
			case '7':	
				controller = 0;
				for (count = 0; count < tamanho; count++) {
					if (vetor[count].disponivel == '1') {
					printf ("O filme na posicao %d e:\n", count);
					imprimefilme(vetor[count]);
					controller++;
					}
				}
				if (controller == 0) {
					printf ("Nao ha filme cadastrado.\n");
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
	
	free (vetor);	/* Liberando a mem�ria alocada pelo vetor */
	return 0;
}

void registrafilme (struct filmes *p) {		//	Fun��o de registrar um �nico filme
	

	printf ("\nDigite o titulo (nome) do filme:\n");	//	Solicitando o nome do filme
	gets(p->titulo);
	
	printf ("\nDigite o genero do filme:\n");			//	Solicitando o genero do filme
	gets (p->genero);
	
	printf ("\nDigite o ano de lancamento filme:\n");	//	Solicitando o ano do filme
	scanf ("%d", &p->ano);
	fflush(stdin);
	
	while (1) {
	printf ("\nDigite o numero de catalogo do filme. \nCuidado para nao cadastrar dois filmes com o mesmo numero de catalogo ;)\n");	
	scanf ("%d", &p->catalogo);				//	Solicitando o numero de catalogo
	fflush(stdin);
	
	if (p->catalogo == 0) {
		printf ("Digite outro valor para ser o numero de catalogo do filme, o 0 e invalido.\n");
		scanf ("%d", &p->catalogo);
	}
	else
		break;
	}
	
	p->disponivel = '1';
}

void leitura (struct filmes *p) {		//	Fun��o de cadastrar todos os filmes
	
	int count;
	
	for (count = 0; count < tamanho; count++) {
		printf ("\n\nRegistrando o %d filme\n", count+1);	//	Intera��o com o usu�rio
		registrafilme (&p[count]);
		system ("cls");
	}
}

void filmes_intervalo (struct filmes *p) {		//	Fun��o de imprimir os filmes no intervalo digitado
	
	int count, ano1, ano2, aux;
	unsigned char controller = '0';

	system("cls");
	printf ("Digite duas datas no formato ano1 ano2\n");	//	Lendo um intervalo
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
	if (controller == '0') {				// 	Exbindo mensagem de insucesso, caso n�o haja filmes registrados no intervalo
		printf ("Nao foi cadastrado nenhum filme neste intervalo.\n");
	}
}

void imprimefilme (struct filmes filminho) {		//	Fun��o que imprime filmes �nicos, recebendo o ponteiro para ele como argumento.
	
	if (filminho.disponivel == '1') {
		printf ("O nome do filme e: %s\n", filminho.titulo);
		printf ("O genero do filme e: %s\n", filminho.genero);
		printf ("O ano do filme e: %d\n", filminho.ano);
		printf ("O numero de catalogo do filme e: %d\n\n", filminho.catalogo);
	}
}

void apaga_registro (struct filmes *p) {	/* Para "apagar" um filme, atribuimos 0 a todos os valores, como se estiv�ssemos dando outro calloc */
	p->ano = 0;												
	p->catalogo = 0;
	p->disponivel = '0';
	strcpy (p->genero, "\0");
	strcpy (p->titulo, "\0");
}

int verifica_catalogo (int num, int *p, struct filmes *vetormain) {		//	Essa funcao recebe um num de catalogo como argumento, um endere�o de mem�ria
																		//	De uma variavel int, que � a posicao atual do vetor na main
	int count, controller = 0;											//	E o endere�o do vetor principal; Retorna 1 em sucesso e 0 caso fracasso		
																		//	1 = h� um filme com tal numero no catalogo; 0 = n�o h�
	for (count = 0; count < tamanho; count++) {
		if (num == vetormain[count].catalogo) {
		*p = count;
		controller = 1;
		break;
		}
	}
	
	return controller;
}

void filmes_genero (struct filmes *p, char string[20]) {	//	Fun��o que filtra os filmes por genero
	
	int count, controller = 0;
	
	printf ("Os filmes cadastrados, do genero \"%s\" sao:\n", string);		//	Intera��o
	
	for (count = 0; count < tamanho; count++) {		//	Filtro
		printf ("\n\n");
		if (stricmp(p[count].genero, string) == 0) {
		controller++;
		imprimefilme (p[count]);
		}
	}
	if (controller == 0)		//	Mensagem de erro, caso n�o haja nenhum filme do genero
	printf ("Nao foi cadastrado nenhum filme desse genero.\n\n");
}

void limpatela() {		//	Fun��o para automatizar a limpeza de tela e deixar o programa mais modularizado e est�tico
	printf ("\n\n\nLimpando a tela...");
	Sleep (2000);
	system ("cls");
}

