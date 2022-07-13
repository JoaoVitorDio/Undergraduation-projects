#ifndef __AUXILIAR__
#define __AUXILIAR__

#include <stdio.h>
typedef struct student student_t;

// funcao que retira o \n de uma string, caso haja algum
void sanitize_string(char *str);

// Função que cria um arquivo file_name. Se ele já existir, limpa todos os seus dados.
// Usada no início do programa para que as próximas aberturas possam ser feitas com o modo
// de abertura "r"
void clean_old_data(char *file_name);

// Recebe uma string como argumento para armazenar a (index_ésima + 1) palavra
// no endereco "parsed_word". Utiliza-se das macros definidas em generaldata.h.
// Como por exemplo, ao receber CSV_COURSE como "index", retorna em parsed_word
// o curso do registro. Ao receber CSV_GRADE, retorna a nota em parsed_word.
unsigned short int parser_csv_string(char *parsed_word, char *string_to_parse, unsigned short int index);

// Lê um registro, se o arquivo nao tiver acabado, e o armazena em student. Retorna 1 em sucesso
// e 0 caso contrário.
unsigned short int read_register(student_t *student, FILE *file_pointer);

// Recebe o ponteiro para o arquivo (na posicao exata em que o registro deve ser escrito)
// e uma string csv como argumento. Armazena as informacoes contidas na string_csv no formato
// student_t no arquivo binário especificado, de forma a ser lida posteriormente pelas demais
// funcoes do programa. Retorna 1 em sucesso, 0 caso contrário.
unsigned short int write_string_data(FILE *file_pointer, char *string_csv);

// retorna o proximo rrn disponivel (fim do arquivo) no arquivo de registros
long getRRNinFile(FILE *file_pointer);

// Imprime o registro de um estudante no formato especificado pelo trabalho
void print_student(student_t *student);

#endif