/*  Projeto desenvolvido pelo aluno Joao Vitor Diogenes para a disciplina 
    de algoritmos e estruturas de dados II, do curso Bacharelado em Sistemas 
    de informação do Instituto de Ciências Matemáticas e de Computação (ICMC - USP).


        Árvore B
    O seguinte trabalho propõe a implementação de uma árvore B para indexação
    de registros de tamanho fixo. A implementação da árvore B deve armazenar nos nós,
    os relative record numbers definidos com o tipo long, alem de variáveis auxiliares de
    controle para manutenção das páginas de disco. Todos os arquivos gerados devem
    estar no formato binário, evitando desperdício de espaço com tipos primitivos.


        Operacoes suportadas e formato das entradas:
    Insercao:
            insert 11899900,"SomeName","SomeForeName","someCourse",8.25

    Busca:
        Na instrucao "search", e necessario passar apenas a chave que deseja buscar
        concatenada com o proprio comando. Segue o exemplo:
            search 11899900
        Caso a chave nao exista, o comando deve retornar "Registro nao encontrado!"

    Update:
        O comando update deve receber um registro com chave ja cadastrada. a estrutura e identica ao
        insert. Caso a chave nao exista, o comando deve retornar "Registro nao encontrado!". Exemplo:
            update 11289521,"OtherName","AnotherName","AnotherCourse",8.25

    Exit:
        Simples comando para sair do programa, segue exemplo:
            exit

        Organização interna do arquivo binário
    Cada registro dentro do arquivo deverá estar estruturado da seguinte forma:

    Numero USP - int
    Nome - char[?]
    Sobrenome - char[?]
    Curso - char[?]
    Nota - float

        Formato de saída:
    −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
    nUSP: 7
    Nome: Anthony
    Sobrenome: Fernando
    Curso: Sistemas de Informacao
    Nota: 9.10
    −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
    −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
    nUSP: 2
    Nome: Vincent
    Sobrenome: James
    Curso: Sistemas de Informacao
    Nota: 9.10
    −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "auxiliar.h"

int main(void)
{
    char file_name[] = "registers_in_binary.bin";
    char tree_file_name[] = "tree_keys.bin";
    clean_old_data(file_name);
    clean_old_data(tree_file_name);

    FILE *tree_file_pointer = fopen(tree_file_name, "r+");
    btPage *root = pegaOuCriaRaiz(tree_file_pointer);

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

        char *operation = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
        unsigned short int success = parser_csv_string(operation, string_being_read, CSV_OP);
        if (!success)
        {
            printf("Erro no parseamento da operacao %s\n", string_being_read);
        }

        sscanf(string_being_read, "%s", operation);


        if (strcmp(operation, "insert") == 0)
        {
            int success = 0;

            char buffer[200];
            success = parser_csv_string(buffer, string_being_read, CSV_USPNUMBER);
            if (!success)
                printf("Algo deu errado no parseamento para pegar o numUSP na insercao\n");

            int found = buscaArvore(root, atoi(buffer), tree_file_pointer);

            if (found == -1)
            {
                FILE *file_pointer = fopen(file_name, "r+");

                long rrn = getRRNinFile(file_pointer);
                fseek(file_pointer, rrn * SIZE_OF_A_REGISTER, SEEK_SET);
                write_string_data(file_pointer, string_being_read);

                fclose(file_pointer);

                record new_record;
                new_record.key = atoi(buffer);
                new_record.recordRRN = rrn;
                insercaoArvore(&new_record, &root, tree_file_pointer);

            }
            else
            {
                printf("O Registro ja existe!\n");
            }
        }
        else if (strcmp(operation, "search") == 0)
        {
            char buffer[SIZE_OF_STRINGS];
            parser_csv_string(buffer, string_being_read, CSV_OPINFO);
            unsigned short int key_to_search = atoi(buffer);

            int register_rrn = buscaArvore(root, key_to_search, tree_file_pointer);
            if (register_rrn == -1)
            {
                printf("Registro nao encontrado!\n");
            }
            else
            {
                FILE *file_pointer = fopen(file_name, "r+");

                fseek(file_pointer, register_rrn * SIZE_OF_A_REGISTER, SEEK_SET);
                student_t student;
                read_register(&student, file_pointer);
                print_student(&student);

                fclose(file_pointer);
            }
        }
        else if (strcmp(operation, "update") == 0)
        {
            char buffer[SIZE_OF_STRINGS];
            parser_csv_string(buffer, string_being_read, CSV_USPNUMBER);
            unsigned short int key_to_search = atoi(buffer);

            int register_rrn = buscaArvore(root, key_to_search, tree_file_pointer);
            if (register_rrn == -1)
            {
                printf("Registro nao encontrado!\n");
            }
            else
            {
                FILE *file_pointer = fopen(file_name, "r+");

                fseek(file_pointer, register_rrn * SIZE_OF_A_REGISTER, SEEK_SET);
                write_string_data(file_pointer, string_being_read);

                fclose(file_pointer);
            }
        }
        else
        {
            printf("Houve um erro na operacao: %s\n", operation);
        }

        free(operation);
        free(string_being_read);
    }

    libera_node(root);
    fclose(tree_file_pointer);

    return 0;
}