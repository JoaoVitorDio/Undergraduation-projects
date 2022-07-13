#include "generaldata.h"
#include "auxiliar.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// funcao que retira o \n de uma string, caso haja algum, e tambem as aspas
// para que possamos utilizar com as mesmas funcoes dos exercicios de indice primario
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

    for (int i = 0; i < size; i++)
    {
        if (str[i] == 34) // 34 == codigo das aspas em ASCII...
        {
            for (int k = i; k < size; k++)
            {
                str[k] = str[k + 1];
            }
            size--;
            i--;
        }
    }
}

// Função que cria um arquivo file_name. Se ele já existir, limpa todos os seus dados.
// Usada no início do programa para que as próximas aberturas possam ser feitas com o modo
// de abertura "r"
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
        parsed_word[i] = '\0';
    }

    return 1;
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

long getRRNinFile(FILE *file_pointer)
{
    fseek(file_pointer, 0, SEEK_END);
    long rrn = ftell(file_pointer) / SIZE_OF_A_REGISTER;
    return rrn;
}

void print_student(student_t *student)
{
    printf("-------------------------------\n");
    printf("nUSP: %d\n", student -> usp_number);
    printf("Nome: %s\n", student -> name);
    printf("Sobrenome: %s\n", student -> surname);
    printf("Curso: %s\n", student -> course);
    printf("Nota: %.2f\n", student -> grade);
    printf("-------------------------------\n");
}