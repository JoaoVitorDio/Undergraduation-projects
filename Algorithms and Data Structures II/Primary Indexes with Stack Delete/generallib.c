#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "generallib.h"
#include "generaldata.h"

// funcao que retira o \n de uma string, caso haja algum
void sanitize_string(char *str)
{
    if (str == NULL)
    {
        return;
    }
    int size = 0;
    size = strlen(str);

    if (!size)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
    }
}

void clean_old_data(char *file_name)
{
    if (file_name == NULL)
    {
        return;
    }
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return;
    }
    fclose(file);
}

unsigned short int size_of_struct()
{
    unsigned short int size = sizeof(int) + sizeof(float) + (sizeof(char) * 30 * 3);
    return (size);
}

// Recebe o ponteiro para o arquivo (na posicao exata em que o registro deve ser escrito)
// e uma string csv como argumento. Armazena as informacoes contidas na string_csv no formato
// student_t no arquivo binário especificado, de forma a ser lida posteriormente pelas demais
// funcoes do programa. Retorna 1 em sucesso, 0 caso contrário.
unsigned short int write_string_data(FILE *file_pointer, char *string_csv)
{
    if (string_csv == NULL || file_pointer == NULL)
    {
        return 0;
    }

    char *buffer = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
    int usp_number = 0;

    assert(parser_csv_string(buffer, string_csv, CSV_USPNUMBER) != 0);
    usp_number = atoi(buffer);

    char *name = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
    assert(parser_csv_string(name, string_csv, CSV_NAME) != 0);

    char *surname = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
    assert(parser_csv_string(surname, string_csv, CSV_SURNAME) != 0);

    char *course = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
    assert(parser_csv_string(course, string_csv, CSV_COURSE) != 0);

    float grade = 0;
    assert(parser_csv_string(buffer, string_csv, CSV_GRADE) != 0);
    grade = atof(buffer);

    // Poderíamos usar uma variável do tipo student_t que criamos e passar todas
    // as informacoes que temos para ela, mas, também podemos escrever diretamente
    // o que temos no arquivo, evitando ações desnecessárias.


    fwrite(&usp_number, sizeof(int), 1, file_pointer);
    fwrite(name, SIZE_OF_STRINGS, 1, file_pointer);
    fwrite(surname, SIZE_OF_STRINGS, 1, file_pointer);
    fwrite(course, SIZE_OF_STRINGS, 1, file_pointer);
    fwrite(&grade, sizeof(float), 1, file_pointer);

    free(course);
    free(name);
    free(surname);
    free(buffer);

    return 1;
}


// Recebe uma string como argumento para armazenar a (index_ésima + 1) palavra
// no endereco "parsed_word"
unsigned short int parser_csv_string(char *parsed_word, char *string_to_parse, unsigned short int index)
{
    if (string_to_parse == NULL || parsed_word == NULL)
    {
        return 0;
    }


    char buffer[SIZE_OF_STRINGS];
    strcpy(buffer, "0");

    unsigned short int commas_found = 0;
    unsigned short int string_index = 0;
    unsigned short int string_size = strlen(string_to_parse);

    // andando na string a ser parseada até chegarmos à parte que nos interessa.
    // Por exemplo, se queremos apenas o curso, que viria com index == 3, teríamos de
    // percorrer na string até encontrar a 3° virgula.
    for (; commas_found < index && string_index < string_size; string_index++)
    {
        if (string_to_parse[string_index] == ',' || string_to_parse[string_index] == ';' ||
            string_to_parse[string_index] == '|')
        {
            commas_found++;
        }
    }

    unsigned short int i = 0;
    for (i = 0;
         string_to_parse[string_index] != ',' && string_to_parse[string_index] != ';' &&
         string_to_parse[string_index] != '|' && string_index < string_size;
         i++, string_index++)
    {
        parsed_word[i] = string_to_parse[string_index];
    }
    parsed_word[i] = '\0';

    // casos especiais: A parte procurada da string é a operação. Porém, a separação da operação para o
    // num_usp é um espaço, e não uma vírgula, mesmo sendo campos diferentes.
    if (index == 0)
    {
        // a operação tem 6 letras, entao colocaremos no espaço 6 do vetor, um string_terminator.
        parsed_word[SIZE_OF_OPERATION] = '\0';
    }
    if (index == 5)
    {
        string_index = SIZE_OF_OPERATION + 1; // 1 se refere ao espaço. Exemplo: INSERT 12345678, Anything.
        // O indice em que o num_usp começa é o indice 7 (oitavo campo do vetor)
        for (i = 0;
             i < string_size && string_index < string_size && string_to_parse[string_index] != ',' &&
             string_to_parse[string_index] != ';' && string_to_parse[string_index] != '|';
             i++, string_index++)
        {
            parsed_word[i] = string_to_parse[string_index];
        }
        // POSSIVEL ERRO: Pode haver algum erro aqui
        parsed_word[i] = '\0';
    }

    return 1;
}

int how_many_indexes()
{
    FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");
    assert(file_index_pointer != NULL);

    int registers_in_index = 0;
    fread(&registers_in_index, sizeof(int), 1, file_index_pointer);

    fclose(file_index_pointer);

    return registers_in_index;
}

int next_rrn()
{
    FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");
    assert(file_index_pointer != NULL);

    int rrn = 0;
    fseek(file_index_pointer, sizeof(int), SEEK_SET);
    fread(&rrn, sizeof(int), 1, file_index_pointer);

    fclose(file_index_pointer);

    return rrn;
}

void create_index_file()
{
    FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "a");

    int registers_in_index = 0;
    int rrn = 0;
    // se file_index_pointer estiver no começo do arquivo, significa que o arquivo não
    // existia e é a nossa primeira interação com ele.
    if (ftell(file_index_pointer) == SEEK_SET)
    {
        fwrite(&registers_in_index, sizeof(int), 1, file_index_pointer);
        fwrite(&rrn, sizeof(int), 1, file_index_pointer);
    }

    fclose(file_index_pointer);
}

index_t *read_indexes_into_ram()
{

    int array_size = how_many_indexes();

    FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");
    assert(file_index_pointer != NULL);

    fseek(file_index_pointer, 0, SEEK_END);

    index_t *indexes = (index_t *) calloc(array_size, sizeof(index_t));

    fseek(file_index_pointer, SIZE_OF_INDEX_HEADER, SEEK_SET);
    for (int i = 0; i < array_size; i++)
    {
        fread(&indexes[i].key, sizeof(int), 1, file_index_pointer);
        fread(&indexes[i].rrn, sizeof(int), 1, file_index_pointer);
    }

    fclose(file_index_pointer);

    return indexes;
}

void sort_with_insertion(index_t *indexes)
{

    int i = 0, j = 0;
    int array_size = how_many_indexes();
    if (array_size < 2)
    {
        return;
    }
    index_t key_to_order;
    key_to_order.key = indexes[array_size - 1].key;
    key_to_order.rrn = indexes[array_size - 1].rrn;

    for (i = 1; i < array_size; i++)
    {
        key_to_order.key = indexes[i].key;
        key_to_order.rrn = indexes[i].rrn;

        j = i - 1;

        while (j >= 0 && indexes[j].key > key_to_order.key)
        {
            indexes[j + 1].key = indexes[j].key;
            indexes[j + 1].rrn = indexes[j].rrn;
            j = j - 1;
        }
        indexes[j + 1].key = key_to_order.key;
        indexes[j + 1].rrn = key_to_order.rrn;
    }
}

index_t *binary_search_key(index_t *indexes, int start, int end, int key)
{
    // end pode ser -1 quando ainda não há nenhum indice no vetor de indices.
    // Se ainda nao há nenhum indice, com certeza ele não está no vetor.
    if (start < 0 || end < 0)
    {
        return NULL;
    }
    assert(indexes != NULL);

    if (indexes[start].key == key)
    {
        return &indexes[start];
    }
    else if (indexes[end].key == key)
    {
        return &indexes[end];
    }

    // se tivermos encontrado, já foi retornado nas verificações acima. Esse é o caso em que
    // nao foi encontrado.
    if (start == end)
    {
        return NULL;
    }

    int half = (int)((start + end) / 2);

    if (key <= indexes[half].key)
    {
        return binary_search_key(indexes, start, half, key);
    }
    else
    {
        return binary_search_key(indexes, half + 1, end, key);
    }
}

// busca binaria pela key que retorna o seu indice no array na RAM
int binary_search_index(index_t *indexes, int start, int end, int key)
{
    // end pode ser -1 quando ainda não há nenhum indice no vetor de indices.
    // Se ainda nao há nenhum indice, com certeza ele não está no vetor.
    if (start < 0 || end < 0)
    {
        return -1;
    }
    assert(indexes != NULL);

    if (indexes[start].key == key)
    {
        return start;
    }
    else if (indexes[end].key == key)
    {
        return end;
    }

    // se tivermos encontrado, já foi retornado nas verificações acima. Esse é o caso em que
    // nao foi encontrado.
    if (start == end)
    {
        return -1;
    }

    int half = (int) ((start + end) / 2);

    if (key <= indexes[half].key)
    {
        return binary_search_index(indexes, start, half, key);
    }
    else
    {
        return binary_search_index(indexes, half + 1, end, key);
    }
}

// recebe uma key e retorna por valor um indice indicando os dados da key recebida como argumento.
// se a key nao for encontrada, index.key == -1 e index.rrn == -1
index_t search_key(int key)
{
    index_t *indexes = read_indexes_into_ram();
    int end = how_many_indexes() - 1;
    int start = 0;
    index_t *index_of_student = binary_search_key(indexes, start, end, key);

    index_t value_backup_index;
    if (index_of_student == NULL)
    {
        // nao posso liberar antes porque nosso index_of_student usado na comparacao
        // é um ponteiro para um dos indices desse vetor.
        free(indexes);
        value_backup_index.key = -1;
        value_backup_index.rrn = -1;
        return value_backup_index;
    }
    value_backup_index.key = index_of_student -> key;
    value_backup_index.rrn = index_of_student -> rrn;

    free(indexes);

    return value_backup_index;
}

// recebe um numero usp como chave_primaria e o nome do arquivo grande.
// Retorna uma estrutura do estudante com o numero usp enviado como argumento por referencia
// (é alocado um registro na heap) ou retorna NULL caso não seja encontrado.
student_t *search_key_in_file(char *file_name, int key)
{
    index_t index = search_key(key);
    if (index.key == -1)
    {
        return NULL;
    }

    FILE *file_pointer = fopen(file_name, "r+");

    fseek(file_pointer, index.rrn * SIZE_OF_A_REGISTER, SEEK_SET);

    student_t *student = (student_t *) calloc(1, sizeof(student_t));

    int error = fread(&student -> usp_number, sizeof(int), 1, file_pointer);
    if (!error) return NULL;

    error = fread(&student -> name, sizeof(char), SIZE_OF_STRINGS, file_pointer);
    if (!error) return NULL;

    error = fread(&student -> surname, sizeof(char), SIZE_OF_STRINGS, file_pointer);
    if (!error) return NULL;

    error = fread(&student -> course, sizeof(char), SIZE_OF_STRINGS, file_pointer);
    if (!error) return NULL;

    error = fread(&student -> grade, sizeof(float), 1, file_pointer);
    if (!error) return NULL;

    fclose(file_pointer);

    return student;
}

// Lê um registro, se o arquivo nao tiver acabado, e o armazena em student. Retorna 1 em sucesso
// e 0 caso contrário.
unsigned short int read_register(student_t *student, FILE *file_pointer)
{
    int error = fread(&student -> usp_number, sizeof(int), 1, file_pointer);
    if (!error) return 0;

    error = fread(&student -> name, sizeof(char), SIZE_OF_STRINGS, file_pointer);
    if (!error) return 0;

    error = fread(&student -> surname, sizeof(char), SIZE_OF_STRINGS, file_pointer);
    if (!error) return 0;

    error = fread(&student -> course, sizeof(char), SIZE_OF_STRINGS, file_pointer);
    if (!error) return 0;

    error = fread(&student -> grade, sizeof(float), 1, file_pointer);
    if (!error) return 0;

    return 1;
}