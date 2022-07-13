/*  Projeto desenvolvido pelo aluno João Vitor Diógenes para a disciplina de
    algoritmos e estruturas de dados II, do curso Bacharelado em Sistemas de
    informação do Instituto de Ciências Matemáticas e de Computação (ICMC - USP).

    O projeto segue um padrão de nomenclatura de variáveis, funções, constantes/macros e afins
    em inglês, com comentários em português. Majoritariamente, o código busca ser auto-explicativo
    e com funcoes pequenas e intuitivas, sem a necessidade de códigos excessivos, valorizando a
    cultura "Keep it Simple".

    */

/*

        Registros de Alunos com Busca por Índices Primários
    Esse exercício consiste na execução de operações de inserção, busca e remoção LOGICA em índices primários

        Qual é a ideia? Ler os comandos da entrada padrão e executa-los sequencialemente. Os comandos são:

    insert: Insere um registro no arquivo binário, a linha estará no formato csv
    search: executa a busca de um registro por meio de sua chave primária
    delete: remove um registro por meio de sua chave primária
    exit: finaliza a execução

    O que é um CSV? Um arquivo CSV(comma-separated-values) é um arquivo texto puro onde os campos de cada registro
    são separados por algum desses caracteres: vírgula, ponto e vírgula, pipe ou espaço. Os separadores mais comuns
    são vírgula e ponto e vírgula. Os campos de texto, em alguns casos, estão entre aspas simples ou duplas.
    Para o nosso caso não há aspas.

        Organização interna do arquivo binário
    Cada registro dentro do arquivo deverá estar estruturado da seguinte forma:

    Numero USP - int
    Nome - char[?]
    Sobrenome - char[?]
    Curso - char[?]
    Nota - float

    Dê o tamanho que achar necessário para os campos CHAR

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filelib.h"
#include "generallib.h"

// TODO : Falta configurar o makefile para rodar no runcodes
int main(void)
{
    char file_name[] = "registers_in_binary.bin";
    clean_old_data(file_name);
    clean_old_data(FILE_OF_INDEX_NAME);
    clean_old_data(FILE_OF_DELETED);

    // Etapa de leitura da stdin e escrita dos dados lidos no arquivo binário.
    while (1)
    {
        // lendo da stdin e interrompendo laço quando encontrado o fim da entrada (EOF)
        char *string_being_read = (char *) calloc(MAX_SIZE_OF_INPUT, sizeof(char));
        // silenciando warning do valgrind de jmp com essa variavel nao inicializada
        void *eof = fgets(string_being_read, MAX_SIZE_OF_INPUT, stdin);
        if (eof == NULL)
        {
            free(string_being_read);
            break;
        }
        sanitize_string(string_being_read);
        if (strcmp(string_being_read, "exit") == 0)
        {
            free(string_being_read);
            break;
        }

        // TODO. Terminar esse laço
        // alocando uma string de tamanho maior que a operacao para nao zoar a parser, já que a separação
        // da operacao para o registro é um espaço e não uma virgula, o parser irá reconhecer (ainda que irá
        // tratar posteriormente) e armazenar na string uma palavra de size_of_op + espaco + usp_number na string.
        char *operation = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
        unsigned short int success = parser_csv_string(operation, string_being_read, CSV_OP);
        sscanf(string_being_read, "%s", operation);
        if (!success)
        {
            printf("Erro no parseamento da operacao %s\n", string_being_read);
        }


        if (strcmp(operation, "insert") == 0)
        {
            success = insert_data_in_file(file_name, string_being_read);
            if (!success)
            {
                printf("O Registro ja existe!\n");
            }
        }
        else if (strcmp(operation, "search") == 0)
        {
            char buffer[SIZE_OF_STRINGS];
            parser_csv_string(buffer, string_being_read, CSV_OPINFO);
            unsigned short int key_to_search = atoi(buffer);
            success = search(file_name, key_to_search);
            if (!success)
            {
                printf("Registro nao encontrado!\n");
            }
        }
        else if (strcmp(operation, "delete") == 0)
        {
            char buffer[SIZE_OF_STRINGS];
            parser_csv_string(buffer, string_being_read, CSV_OPINFO);
            unsigned short int usp_number = atoi(buffer);
            success = delete_register(file_name, usp_number);
            if (!success)
            {
                // Nao há saída de erro para a remoção na saída esperada
            }
        }
        else if (strcmp(operation, "sequential") == 0)
        {
            success = sequential_print(file_name);
            if (!success)
            {
                printf("Erro na impressao sequencial!\n");
            }
        }
        else
        {
            printf("Houve um erro na operacao: %s\n", operation);
        }

        free(operation);
        free(string_being_read);
    }


    return 0;
}