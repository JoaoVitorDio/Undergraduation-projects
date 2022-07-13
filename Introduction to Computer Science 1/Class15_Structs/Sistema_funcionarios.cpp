#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*	Exercício 4 e 5 - aula 15 - Sistema que registra funcionarios e imprime seus dados, com algumas regras de negócio	*/

#define TOTAL 100

struct funcionario {
	char numerofunc[10];
	char nome[50];
	unsigned int idade;
	char telefone[10];
	char cargo[10];
	float salario;
};

struct funcionario registrafuncionario ();
void exibefuncionario (struct funcionario func);
void registratodos (struct funcionario *func, int total);
void printatodos (struct funcionario *func, int total);
void limpatela ();


int main () {
	
	struct funcionario func[TOTAL];
	int count = 0, controller, sucesso = 0;
	char menu, loop = '1';
	char string[50]; //	String de comparação
	
	
	while (loop == '1') {
		//	Menu
		printf ("\n\nDigite a acao que deseja fazer;\n\n");
		printf ("\nPara registrar todos os 100 funcionarios, digite 1.\n");
		printf ("\nPara exibir todos os 100 funcionarios, digite 2.\n");
		printf ("\nPara visualizar um funcionario especifico, digite 3.\n");
		printf ("\nPara alterar um cadastro especifico, digite 4.\n");
		
		printf ("\nDigite 0 caso queira fechar o menu.\n\n");
		
		printf ("Digite 9 caso queira limpar a tela.\n\n\n");
			
		scanf ("%c", &menu);
		fflush(stdin);
			
		switch (menu) {
			case '9':
				limpatela();
				break;
			case '0':
				return 0;
			case '1':
				registratodos (&func[0], TOTAL);
				break;	
			case '2':
				printatodos (&func[0], TOTAL);
				break;
			case '3':
				printf ("\nDigite 1 para buscar pelo nome, digite 2 para buscar pelo numero\n");
				scanf ("%d", &controller);
				fflush (stdin);
				
				switch (controller) {
					case 1:
						printf ("\nDigite o nome do funcionario.\n");
						gets (string);
						for (count = 0; count < TOTAL; count++) {
							if (stricmp(func[count].nome, string) == 0) {
								exibefuncionario (func[count]);
								sucesso = 1;
							}	
						}
						
						if (sucesso == 0)
							printf ("\nNao ha nenhum usuario cadastrado com esse nome.");
							
						break;
					
					case 2:				
						printf ("\nDigite o numero do funcionario.\n");
						gets (string);
						for (count = 0; count < TOTAL; count++) {
							if (stricmp(func[count].numerofunc, string) == 0) {
								exibefuncionario (func[count]);
								sucesso = 1;
							}
						}
						if (sucesso == 0) {
							printf ("\nNao ha nenhum usuario cadastrado com esse numero.");
							limpatela();
							}
						break;
						
					default: 
					printf ("\nComando invalido!\n");
					limpatela();
				}
				break;
			case '4':
				printf ("\nDigite 1 para alterar os dados de um funcionario, buscando-o pelo nome\n");
				printf("Ou digite 2, para alterar os dados de um numero de registro no sistema.\n");
				scanf ("%d", &controller);
				
				switch (controller) {
					case 1:
						printf ("\nDigite o nome do funcionario que deseja alterar os dados:\n");
						gets (string);
				
					for (count = 0; count < TOTAL; count++) {
						if (stricmp(func[count].nome, string) == 0) {
							func[count] = registrafuncionario();
						}
						else 
							printf ("\nNao ha nenhum usuario cadastrado com esse nome.");
					} 
					break;
					
					case 2:
						printf ("\nDigite o numero de registro no sistema que deseja cadastrar ou alterar um dado.\n");
						scanf ("%d", &count);
						fflush(stdin);
						
						printf ("Registrando os dados da posicao %d...", count);
						func[count] = registrafuncionario();
					break;
						
					default:
						printf ("\n\nComando invalido. Retornando ao menu...\n");
						
				}
				break;
				
			default:
				printf ("Comando invalido!\n");
				printf ("Deseja voltar ao menu? Digite 1 caso sim, e 0 caso nao.\n");
				scanf ("%c", &loop);
				fflush(stdin);
		}
	}
	
	/*	Preciso fazer as funções que imprimem todos os funcionarios, o menu de abertura com switch case... E a função de procura	*/
	
	return 0;
}

void printatodos (struct funcionario *func, int total) {
	int count;
	
	for (count = 0; count < total; count++) {
		printf ("\n\nO funcionario %d possui os dados:\n", count+1);
		exibefuncionario (func[count]);	
	}
}

void registratodos (struct funcionario *func, int total) {	
	int count;
	for (count = 0;count < total; count++) {
		printf ("\n\nRegistre o funcionario %d\n\n", count+1);
		func[count] = registrafuncionario();
	}	
}

struct funcionario registrafuncionario () {
	/* 	Essa é a função de registro de determinado funcionario, recebido como argumento. Para que
	determinado funcionario receba os valores, é determinado utilizar ela da forma Func = registrafuncionario(func[tal]);	*/
	
	struct funcionario func;
	
	printf ("\nDigite o numero do funcionario\n");
	gets(func.numerofunc);

	printf ("Digite o nome do funcionario\n");
	gets(func.nome);
	
	printf ("Digite a idade do funcionario\n");
	scanf ("%u", &func.idade);
	fflush(stdin);
	
	printf ("Digite o telefone do funcionario\n");
	gets(func.telefone);
	
	printf ("Digite o cargo do funcionario\n");
	gets(func.cargo);
	
	printf ("Digite o salario do funcionario\n");
	scanf ("%f", &func.salario);
	fflush(stdin);
	
	return func;
}

void exibefuncionario (struct funcionario func) {
	/*	Essa é a função primitiva, que realmente imprime UM determinado funcionario, que foi recebido por parametros	*/
	printf ("\n\nO numero do funcionario e: %s", func.numerofunc);
	printf ("\nO nome do funcionario e: %s", func.nome);
	printf ("\nA idade do funcionario e: %u", func.idade);
	printf ("\nO telefone do funcionario e: %s", func.telefone);
	printf ("\nO cargo do funcionario e: %s", func.cargo);
	printf ("\nO salario do funcionario e: %.2f", func.salario);
}

void limpatela() {
	printf ("\nRetornando ao menu...");
	Sleep(3000);
	system("cls");
}

