#ifndef GENERALLIB_H_
#define GENERALLIB_H_

/*
    Generallib = TAD intermediário que implementa as funções utilizadas pela filelib.c, de forma
    mais "encapsulada"
*/

/*
Header do arquivo de indice primario:
#number_of_registers_in_index_file#next_RRN_in_register_file

OBS: É importante manter ambos dados porque, visto que trabalharemos com remoção
lógica dos registros, o arquivo de índices pode ter uma quantia de índices menor do
que a quantia de espaços ocupados por registros no arquivo grande.

Organização dos dados da pilha para remoção: Armazenam-se apenas os RRNs removidos. O último
registro no arquivo de removidos é o último a ser removido e é nele que deve ser inserido.

Header dos deleted:
#RRNTopoDaPilha
*/

#include "generaldata.h"

struct student
{
    int usp_number;
    char name[SIZE_OF_STRINGS], surname[SIZE_OF_STRINGS], course[SIZE_OF_STRINGS];
    float grade;
};

typedef struct struct_index
{
    int key;
    int rrn;
}   index_t;

typedef struct student student_t;

// funcao que retira o \n de uma string, caso haja algum
void sanitize_string(char *str);

// Função que cria um arquivo file_name. Se ele já existir, limpa todos os seus dados.
// Usada no início do programa para que as próximas aberturas possam ser feitas com o modo
// de abertura "r"
void clean_old_data(char *file_name);

unsigned short int size_of_struct();

// Recebe o ponteiro para o arquivo (na posicao exata em que o registro deve ser escrito)
// e uma string csv como argumento. Armazena as informacoes contidas na string_csv no formato
// student_t no arquivo binário especificado, de forma a ser lida posteriormente pelas demais
// funcoes do programa. Retorna 1 em sucesso, 0 caso contrário.
unsigned short int write_string_data(FILE *file_pointer, char *string_csv);

// Recebe uma string como argumento para armazenar a (index_ésima + 1) palavra
// no endereco "parsed_word"
unsigned short int parser_csv_string(char *parsed_word, char *string_to_parse, unsigned short int index);

// Funcoes "intermediarias", usadas na filelib.
// lê do header do arquivo de indices, a quantia atual de indices
int how_many_indexes();

// lê do header do arquivo de indices, o proximo rrn a ser usado.
int next_rrn();

// Cria um novo arquivo de indices. Seta as informações iniciais do header.
void create_index_file();

// Retorna um vetor alocado dinamicamente contendo os índices lidos do arquivo de índice
index_t *read_indexes_into_ram();

// ordenação do vetor da HEAP com o método insertion
void sort_with_insertion(index_t *indexes);

// recebe uma key e retorna por valor um indice indicando os dados da key recebida como argumento.
// se a key nao for encontrada, index.key == -1 e index.rrn == -1
index_t search_key(int key);

// Busca binaria pela key no vetor alocado dinamicamente recebido como argumento.
// Retorna o endereço do indice com a key procurada, no vetor em uso. Retorna NULL caso
// não encontre.
index_t *binary_search_key(index_t *indexes, int start, int end, int key);

// Busca binaria pela key no vetor alocado dinamicamente recebido como argumento.
// Retorna o indice em que está a key no vetor em uso. Retorna -1 caso não encontre.
int binary_search_index(index_t *indexes, int start, int end, int key);

// Recebe um numero usp como chave_primaria e o nome do arquivo grande.
// Retorna uma estrutura do estudante com o numero usp enviado como argumento por referencia
// (é alocado um registro na heap) ou retorna NULL caso não seja encontrado.
student_t *search_key_in_file(char *file_name, int key);

// Lê um registro, se o arquivo nao tiver acabado, e o armazena em student. Retorna 1 em sucesso
// e 0 caso contrário.
unsigned short int read_register(student_t *student, FILE *file_pointer);

#endif // GENERALLIB_H_