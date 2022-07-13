/*  Projeto desenvolvido pelo aluno João Vitor Diógenes para a disciplina de
    algoritmos e estruturas de dados, do curso Bacharelado em Sistemas de
    informação do Instituto de Ciências Matemáticas e de Computação (ICMC - USP).

    O tamanho de cada verbete/definicao com que o programa trabalha em cada dicionario
    é estático, porém adaptável à mudança do usuário, basta alterar o header dictionary.h.

    O projeto segue um padrão de nomenclatura de variáveis, funções, constantes/macros e afins
    em inglês, com comentários em português. Majoritariamente, o código busca ser auto-explicativo
    e com funcoes pequenas e intuitivas, sem a necessidade de códigos excessivos, valorizando a
    cultura "Keep it Simple".

    */

/*
        Creditos quanto a elaboração do Problema:
    Professor Marcelo Garcia Manzato e alunos PAE Andre Zanon e Luan Souza.

        Descricao
    O objetivo deste projeto e desenvolver os mecanismos de manipulacao de um dicionario com definicoes
    de palavras ou expressoes idiomaticas (verbetes) apresentadas pelos usuarios. O seu dicionario deve
    suportar as operacoes de insercao, remocao, alteracao e busca de palavras, alem da impressao de todos
    os verbetes iniciados por um caractere definido pelo usuario.
    A entrada do programa se da pela definicao da operacao a ser realizada seguida por uma ou duas
    cadeias de caracteres, dependendo da operacao requerida. As operacoes devem considerar a seguinte
    configuracao de entrada:

    • insercao str1 str2 : insere a palavra str1, com a definicao str2, no dicionario;
    • alteracao str1 str2 : altera a definicao da palavra str1 para str2 ;
    • remocao str1 : remove a palavra str1 do dicionario;
    • busca str1 : imprime a definicao da palavra str1 ;
    • impressao ch1 : imprime todas as palavras iniciadas pelo caractere ch1 seguidas por suas respectivas
    definicoes em ordem alfabetica. Cada palavra (com sua respectiva definicao) deve ser impresso em
    uma linha diferente.

    Note que ha operacoes que nao podem ser completadas em alguns casos. Especificamente, essas
    operacoes sao a alteracao, remocao e busca de palavras inexistentes no dicionario e a insercao de uma
    palavra repetida. Nesses casos, o seu programa deve imprimir “OPERACAO INVALIDA”. Caso nao
    haja palavras iniciadas por ch1, mas o usuario requeira a impressao de todas as palavras iniciadas por
    esse caractere, seu programa deve imprimir a mensagem “NAO HA PALAVRAS INICIADAS POR ch1”.
    Um verbete possui ate 50 caracteres, e nao pode conter espacos entre os demais caracteres. A definicao
    de um verbete do dicionario pode conter, no maximo, 140 caracteres, incluindo espacos.
    Lembre-se que seu dicionario deve ser implementado utilizando-se a estrutura de dados skip lists.
    Qualquer estrutura de dados que exija busca linear nao passara em todos os casos de teste por limite de
    tempo de execucao.


        Exemplo
        Entradas
    insercao trauliteiro pessoa rude
    remocao cliche
    insercao cliche acao ou fala previsivel devido ao uso excessivo
    busca trauliteiro
    alteracao cliche palavra ou frase utilizada em excesso
    insercao cessionario pessoa beneficiada com a cessao
    impressao c

        Saidas
    OPERACAO INVALIDA
    trauliteiro pessoa rude
    cessionario pessoa beneficiada com a cessao
    cliche palavra ou frase utilizada em excesso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dictionary.h"

// a maior palavra de operacao é "impressao", com 9 caracteres.
#define SIZE_OF_OP 10

// funcao que retira o \n de uma string, caso haja algum
void sanitize_string(char *str);

int main()
{
    // uso especificado pelo header do TAD
    srand(time(NULL));

    dictionary_t *dic = dictionary_create();
    while (1)
    {
        char operation[SIZE_OF_OP];
        short int isEOF = scanf("%s ", operation);
        if (isEOF == EOF)
            isEOF = 1;
        else
            isEOF = 0;

        if (isEOF)
            break;

        if (strcmp(operation, "insercao") == 0)
        {
            char word[SIZE_OF_VERBETE];
            char definition[SIZE_OF_DEFINITION];
            scanf("%s ", word);
            fgets(definition, SIZE_OF_DEFINITION, stdin);
            sanitize_string(definition);
            unsigned short int success = dictionary_insert(dic, word, definition);
            if (!success)
            {
                printf("OPERACAO INVALIDA\n");
            }
        }
        else if (strcmp(operation, "alteracao") == 0)
        {
            char word[SIZE_OF_VERBETE];
            char def_to_change[SIZE_OF_DEFINITION];
            scanf("%s ", word);
            fgets(def_to_change, SIZE_OF_DEFINITION, stdin);
            sanitize_string(def_to_change);
            unsigned short int success = dictionary_change(dic, word, def_to_change);
            if (!success)
            {
                printf("OPERACAO INVALIDA\n");
            }
        }
        else if (strcmp(operation, "remocao") == 0)
        {
            char word[SIZE_OF_VERBETE];
            scanf("%s", word);
            unsigned short int success = dictionary_remove(dic, word);
            if (!success)
            {
                printf("OPERACAO INVALIDA\n");
            }
        }
        else if (strcmp(operation, "busca") == 0)
        {
            char word[SIZE_OF_VERBETE];
            scanf("%s", word);
            // a operacao "busca" se utiliza da funcao "print_word" porque
            // esse é o resultado esperado da funcao busca na descricao do projeto.
            unsigned short int success = dictionary_print_word(dic, word);
            if (!success)
            {
                printf("OPERACAO INVALIDA\n");
            }
        }
        else if (strcmp(operation, "impressao") == 0)
        {
            char initial_letter = 0;
            scanf("%c", &initial_letter);
            unsigned short int success = dictionary_print_letter(dic, initial_letter);
            if (!success)
            {
                printf("NAO HA PALAVRAS INICIADAS POR %c\n", initial_letter);
            }
        }
    }
    dictionary_destroy(dic);

    return 0;
}

void sanitize_string(char *str)
{
    unsigned short int tamanho = strlen(str);

    for (int i = 0; i < tamanho; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
    }
}