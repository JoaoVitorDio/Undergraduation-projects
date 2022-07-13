/*	Trabalho 5 - Introdu��o � Ci�ncia da computa��o.
	
	Fa�a um programa que abra 2 arquivos de texto j� existentes e mostre as palavras que est�o presentes em ambos os arquivos.
	Obs: Em uma vers�o mais b�sica, as palavras repetidas podem ser apresentadas na tela m�ltiplas vezes. Na vers�o ideal, 
	as palavras repetidas devem ser apresentadas uma �nica vez na tela.
	Trabalhem na vers�o ideal somente ap�s concluir a vers�o simples. */

#include <stdio.h>
#include <string.h>

int main () {
	
	char palavra1[20], palavra2[20], resultado[100][20];	//	Palavra1 armazena as palavras do texto 1 que ser�o comparados com as palavras2 retiradas do arquivo2
	int count = 0, i, j, k, count2;							//	Resultado ser� a matriz em que alocaremos as palavras que aparecem em ambos textos
	
	FILE *arq1, *arq2;			//	Criando e abrindo os arquivos de texto a serem lidos e comparados
	
	arq1 = fopen("texto1.txt", "r+");
	if (arq1 == NULL) {
		printf ("\nErro ao abrir arquivo.\n");
	}
	
	arq2 = fopen ("texto2.txt", "r+");
	if (arq2 == NULL) {
		printf ("\nErro ao abrir arquivo.\n");
	}
	
	while (feof(arq1) == 0) {			//	Leremos todas as palavras do texto1, enquanto n�o estivermos no fim do arquivo.
		fscanf (arq1, "%s", &palavra1);	//	Armazenaremos a palavra atual em palavra1
		fseek(arq2, 0, SEEK_SET);		//	� necess�rio colocar o "cursos" no 0 ao fim de cada while abaixo, para que comecemos a ler o texto novamente
		while (feof(arq2) == 0) {		//	Aqui, come�amos a ler todas as palavras do texto2 e compar�-las com a palavra do texto1 armazenada em palavra1
			fscanf (arq2, "%s", &palavra2);
			if (stricmp(palavra1, palavra2) == 0) {
				strcpy (resultado[count], palavra2);	//	Cada palavra que estiver em ambos, ser� copiada para nossa matriz de resultados.
				count++;
			}
		}
	}
	
	fclose (arq1);	//	Fechando os arquivos
	fclose (arq2);
						
						/*	Para que as palavras que aparecem mais de duas vezes n�o sejam impressas diversas vezes, a estrat�gia �:
						Verificar a nossa matriz de resultados; quando alguma palavra da matriz for igual a outra palavra da matriz, 
						a posi��o dessa segunda palavra ser� sobrescrita pela palavra a seguir, e todas as palavras a seguir, pela diante.
						Fazendo isso at� o fim, exclu�mos a palavra repetida e adiantamos todas as palavras na matriz em uma posi��o. */
						
	count2 = count;		//	count2 � a vari�vel em que armazenaremos o atual n�mero de palavras em ambos textos, sem repeti��es.
	
	for (i = 0; i < count2; i++) {
		strcpy (palavra1, resultado[i]);	//	Armazenando uma palavra da matriz de resultado na variavel palavra1 para compar�-la � todas as outras palavras 
		
		for (j = i+1; j < count2; j++) {	//	Verifica��o da palavra1 com todas as que est�o � sua frente na matriz de resultados
			
			if (strcmp (palavra1, resultado[j]) == 0) {
				for (k = j; (k+1) < count2; k++) {
					strcpy (resultado[k], resultado[k+1]);
				}
				strcpy (resultado[count2], "\0");	//	 Colocando um valor "nulo" nas ultimas posi��es, que agora est�o ocupadas por palavras repetidas.
				count2--;
				j--;
			}
		}
	}
	
	if (count2 == 0) 	//	Verificacao de conteudo
	printf ("Nao ha palavras comuns aos dois arquivos de texto. \n\n(O programa e sensivel a letra maiusculas e minusculas)");
	
	else {
		printf ("As palavras que estao presentes nos dois arquivos de texto, sao:\n\n");	//	Impress�o final...
		for (i = 0; i < count2; i++) {
			printf ("%s\n", resultado[i]);
		}
	}
	
	return 0;
}
