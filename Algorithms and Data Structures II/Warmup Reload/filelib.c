#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "filelib.h"

struct student
{
    int usp_number;
    char name[SIZE_OF_STRINGS], course[SIZE_OF_STRINGS];
    float grade;
};

// Funcoes intermediarias.

// Lê um único registro e o armazena no endereço único passado como argumento.
unsigned short int read_a_register(FILE *file, student_t *student);

// funcao que retira o \n de uma string, caso haja algum
void sanitize_string(char *str);

unsigned short int size_of_struct()
{
    return (sizeof(int) + sizeof(float) + SIZE_OF_STRINGS * 2 * sizeof(char));
}


// Funcoes do TAD:

// Cria e inicializa uma lista de estudantes. Recebe como argumento
// o nome do arquivo a ser lido (para que o espaço seja otimizado)
// e retorna o endereço da primeira posicao da lista.
student_t *student_list_create(char *file_name, unsigned short int *size_of_list)
{
    FILE *file = fopen(file_name, "r+");
    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);

    unsigned short int size_of_register = size_of_struct();
    unsigned short int number_of_registers = (ftell(file) / size_of_register);
    student_t *student_list = (student_t *) calloc(number_of_registers, sizeof(student_t));
    *size_of_list = number_of_registers;

    fclose(file);

    return student_list;
}

// Le todos os dados existentes no arquivo binario e os armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_all_data(char *file_name, student_t *student_list, unsigned short int size_of_list)
{
    if (file_name == NULL || student_list == NULL)
    {
        return 0;
    }

    FILE *file = fopen(file_name, "r+");
    if (file == NULL)
    {
        return 0;
    }

    for (int i = 0; i < size_of_list; i++)
    {
        unsigned short int error = 0;
        error = read_a_register(file, &student_list[i]);
        if (!error)
        {
            return 0;
        }
    }
    fclose(file);

    return 1;
}

// Le a primeira metade do arquivo binario e os armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_first_half(char *file_name, student_t *student_list, unsigned short int size_of_list)
{
    if (file_name == NULL || student_list == NULL)
    {
        return 0;
    }

    FILE *file = fopen(file_name, "r+");
    if (file == NULL)
    {
        return 0;
    }

    for (int i = 0; i < ceil(size_of_list / 2); i++)
    {
        unsigned short int error = 0;
        error = read_a_register(file, &student_list[i]);
        if (!error)
        {
            return 0;
        }
    }
    fclose(file);

    return 1;
}

// Le a segunda metade do arquivo binario e os armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_last_half(char *file_name, student_t *student_list, unsigned short int size_of_list)
{
    if (file_name == NULL || student_list == NULL)
    {
        return 0;
    }

    FILE *file = fopen(file_name, "r+");
    if (file == NULL)
    {
        return 0;
    }

    // Alterando a posicao do ponteiro do arquivo para o registro do meio
    int bytes_ahead = ((size_of_list / 2) * size_of_struct());
    fseek(file, bytes_ahead, SEEK_SET);

    // usaremos a mesma estrutura do laco de repeticao anterior porque a quantia
    // de elementos no vetor student_list sera a mesma. Ambos lidam com metades
    // inclusivas, logo, sao do mesmo temanho.
    for (int i = 0; i < ceil(size_of_list / 2); i++)
    {
        unsigned short int error = 0;
        error = read_a_register(file, &student_list[i]);
        if (!error)
        {
            return 0;
        }
    }
    fclose(file);

    return 1;
}

// Le uma determinada faixa do arquivo binario e os armazena no endereco
// passado como argumento. Recebe como argumento a posicao do primeiro
// registro a ser considerado e a posicao do ultimo registro a ser considerado.
// Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_specified_data(char *file_name, student_t *student_list,
                                       unsigned int initial_position, unsigned int final_position)
{
    if (file_name == NULL || student_list == NULL || (initial_position > final_position))
    {
        return 0;
    }

    FILE *file = fopen(file_name, "r+");
    if (file == NULL)
    {
        return 0;
    }

    // Alterando a posicao do ponteiro do arquivo para a posicao inicial
    int bytes_ahead = ((initial_position - 1) * size_of_struct());
    fseek(file, bytes_ahead, SEEK_SET);

    unsigned short int registers_to_read = final_position - initial_position;


    for (int i = 0; i <= registers_to_read; i++)
    {
        unsigned short int error = 0;
        error = read_a_register(file, &student_list[i]);
        // Se houve algum erro com o fread, significa que o arquivo é invalido ou acabou.
        // Ja fizemos a verificacao do arquivo ser invalido no inicio da funcao, logo,
        // quando read_a_register retornar um erro, significa que terminamos de ler o arquivo
        // e devemos parar. Assim, impedimos que uma faixa maior que o tamanho do arquivo e
        // acima da quantia de registros cadastrados seja lida.
        if (!error)
        {
            break;
        }
    }

    fclose(file);

    return 1;
}

// Le um unico registro, passado como argumento, e o armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_single_data(char *file_name, student_t *student_list, unsigned int position)
{
    if (file_name == NULL || student_list == NULL || position < 1)
    {
        return 0;
    }

    FILE *file = fopen(file_name, "r+");
    if (file == NULL)
    {
        return 0;
    }

    // Alterando a posicao do ponteiro do arquivo para a posicao indicada
    int bytes_ahead = ((position - 1) * size_of_struct());
    fseek(file, bytes_ahead, SEEK_SET);

    unsigned short int error = 0;
    error = read_a_register(file, &student_list[0]);
    if (!error)
    {
        return 0;
    }

    fclose(file);

    return 1;
}

// Imprime no formato especificado pelo exercicio, todo o conteudo da lista/endereco
// passado como argumento. Recebe como argumento o tamanho do vetor para itera-lo.
unsigned short int print_data(student_t *student_list, unsigned short int size_of_list)
{
    if (student_list == NULL)
    {
        return 0;
    }

    for (int i = 0; i < size_of_list; i++)
    {
        // Solucao para que nao imprimamos os valores ainda nao preenchidos, necessaria nos
        // casos de funcoes como a ler apenas metade ou ler apenas um registro especifico.
        // Usa-se o usp_number como identificador, logo, se nao ha numero usp, nao
        // ha registro para imprimir.
        if (student_list[i].usp_number == 0)
        {
            continue;
        }

        // lidando com a formatacao esperada
        if (i > 0)
        {
            printf("\n");
        }

        printf("nUSP: %d\n", student_list[i].usp_number);
        printf("Nome: %s\n", student_list[i].name);
        printf("Curso: %s\n", student_list[i].course);
        printf("Nota: %.2f\n", student_list[i].grade);
    }
    return 1;
}

// Libera a memoria utilizada pelo vetor de alunos.
void student_list_destroy(student_t *student_list)
{
    if (student_list != NULL)
    {
        free(student_list);
    }
}

unsigned short int read_a_register(FILE *file, student_t *student)
{
    unsigned short int error = 0;

    error = fread(&student -> usp_number, sizeof(int), 1, file);
    if (!error)
    {
        return 0;
    }

    error = fread(&student -> name, sizeof(char), SIZE_OF_STRINGS, file);
    if (!error)
    {
        return 0;
    }

    error = fread(&student -> course, sizeof(char), SIZE_OF_STRINGS, file);
    if (!error)
    {
        return 0;
    }

    error = fread(&student -> grade, sizeof(float), 1, file);
    if (!error)
    {
        return 0;
    }

    return 1;
}

// **************** Funcoes do warmup reload ***************


// Le os ultimos 10 (ou o numero definido) registros do arquivo binario e os armazena
// no endereco passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_last_data(char *file_name, student_t *student_list)
{
    if (file_name == NULL || student_list == NULL)
    {
        return 0;
    }

    FILE *file = fopen(file_name, "r+");
    if (file == NULL)
    {
        return 0;
    }

    // iniciando limite da nossa leitura
    unsigned short int registers_to_read = LAST_REGISTERS;
    // Alterando a posicao do ponteiro do arquivo para a posicao inicial
    int bytes_back = (LAST_REGISTERS * size_of_struct());


    fseek(file, 0, SEEK_END);
    int size_of_file_in_bytes = ftell(file);
    fseek(file, 0, SEEK_SET);

    if ((size_of_file_in_bytes - bytes_back) < 0)
    {
        registers_to_read = size_of_file_in_bytes / size_of_struct();
    }
    else
    {
        fseek(file, -bytes_back, SEEK_END);
    }


    for (int i = 0; i < registers_to_read; i++)
    {
        unsigned short int error = 0;
        error = read_a_register(file, &student_list[i]);
        // Se houve algum erro com o fread, significa que o arquivo é invalido ou acabou.
        // Ja fizemos a verificacao do arquivo ser invalido no inicio da funcao, logo,
        // quando read_a_register retornar um erro, significa que terminamos de ler o arquivo
        // e devemos parar. Assim, impedimos que uma faixa maior que o tamanho do arquivo e
        // acima da quantia de registros cadastrados seja lida.
        if (!error)
        {
            break;
        }
    }

    fclose(file);

    return 1;
}

// Recebe o nome de um arquivo e uma string csv como argumento. Armazena as informacoes contidas
// na string_csv no formato student_t no arquivo binário especificado, de forma a ser lida
// posteriormente pelas demais funcoes do programa. Retorna 1 em sucesso, 0 caso contrário.
unsigned short int write_string_data(char *file_name, char *string_csv)
{
    if (string_csv == NULL || file_name == NULL)
    {
        return 0;
    }
    int size_of_string = strlen(string_csv);

    // Nesta função, faremos o "parseamento" da string "linha" csv recebida como argumento em
    // 4 variáveis (correspondentes aos campos do registro): numUSP, nome, curso e nota.

    // A estratégia será usar laços sucessivos, armazenando o índice que usamos para percorrer
    // a string "linha" em csv e armazenando o conteúdo de cada pedaço em uma variável diferente.

    // Faremos em uma única função visto que são laços de lógica simples e a complexidade
    // é a melhor possível.


    // Lendo "campo" por campo da string e armazenando nos devidos atributos da struct.
    // Não será adicionada verificação de espaços como separados do csv, visto que os nomes
    // das pessoas, assim como o curso, pode possuir espaços e ainda ser do mesmo campo.

    char buffer[SIZE_OF_STRINGS];
    strcpy(buffer, "0");

    // lendo o numero USP


    // i acompanhará o indice do buffer e index acompanhará o indice da string_csv
    unsigned short int index = 0;
    unsigned short int i = 0;

    for (i = 0, index = 0;
         i < SIZE_OF_STRINGS && index < size_of_string &&
         string_csv[index] != ',' && string_csv[index] != ';' && string_csv[index] != '|';
         i++, index++)
    {
        buffer[i] = string_csv[index];
    }
    buffer[i] = '\0';
    index++;

    int usp_number = atoi(buffer);


    // Lendo o nome do aluno

    char *name = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
    // i acompanhará o indice do buffer e index acompanhará o indice da string_csv
    for (i = 0;
         index < size_of_string &&
         string_csv[index] != ',' && string_csv[index] != ';' && string_csv[index] != '|';
         i++, index++)
    {
        buffer[i] = string_csv[index];
    }
    index++;
    buffer[i] = '\0';
    strcpy(name, buffer);

    // Lendo o curso do aluno

    char *course = (char *) calloc(SIZE_OF_STRINGS, sizeof(char));
    // i acompanhará o indice do buffer e index acompanhará o indice da string_csv
    for (i = 0;
         index < size_of_string &&
         string_csv[index] != ',' && string_csv[index] != ';' && string_csv[index] != '|';
         i++, index++)
    {
        buffer[i] = string_csv[index];
    }
    index++;
    buffer[i] = '\0';
    strcpy(course, buffer);


    // Lendo a nota do aluno

    float grade = 0.0;
    // i acompanhará o indice do buffer e index acompanhará o indice da string_csv
    for (i = 0;
         index < size_of_string &&
         string_csv[index] != ',' && string_csv[index] != ';' && string_csv[index] != '|';
         i++, index++)
    {
        buffer[i] = string_csv[index];
    }
    index++;
    buffer[i] = '\0';
    grade = atof(buffer);

    // Poderíamos usar uma variável do tipo student_t que criamos e passar todas
    // as informacoes que temos para ela, mas, também podemos escrever diretamente
    // o que temos no arquivo, evitando ações desnecessárias.
    FILE *file = fopen(file_name, "a+");
    if (file == NULL)
    {
        return 0;
    }

    fwrite(&usp_number, sizeof(int), 1, file);
    fwrite(name, SIZE_OF_STRINGS, 1, file);
    fwrite(course, SIZE_OF_STRINGS, 1, file);
    fwrite(&grade, sizeof(float), 1, file);

    free(course);
    free(name);

    fclose(file);


    return 1;
}

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