#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "filelib.h"
#include "generallib.h"
#include "generaldata.h"

// Recebe o nome de um arquivo e uma string em csv como argumento. Armazena
// o registro contido na string, no arquivo de nome passado como argumento,
// utilizando-se do arquivo de indices primarios indexes.bin. Retorna 1 caso sucesso
// e 0 caso contrário
unsigned short int insert_data_in_file(char *file_name, char *string_csv)
{
    if (file_name == NULL || string_csv == NULL)
    {
        return 0;
    }

    // criando o arquivo de indices, caso ele não exista (visto que operaremos utilizando r+)
    create_index_file();

    // garantindo que não estamos inserindo um registro que já existe e informando possível erro
    char buffer[SIZE_OF_STRINGS];
    assert(parser_csv_string(buffer, string_csv, CSV_USPNUMBER) != 0);
    int key = atoi(buffer);
    index_t index = search_key(key);
    if (index.key != -1)
    {
        return 0;
    }

    // Agora que já lidamos com possíveis erros e garantimos um terreno preparado, iremos seguir as
    // seguintes etapas para que a função faça o necessário:

    // Etapa 1 : Escrever o registro recebido no arquivo de registros.
    // Etapa 2 : Guardar o rrn usado para escrever no arquivo grande e escrever o
    //           próximo rrn disponível no header, preparando para a próxima inserção.
    // Etapa 3 : Escrever a chave primaria e o rrn usado para acessá-la no fim do arquivo de indices.
    // Etapa 4 : Escrever a nova quantia de índices no arquivo de índices.
    // Etapa 5 : Re-ordenar o arquivo de índices a partir das chaves primarias. E reescrever os índices
    //           no arquivo de índice.

    // Etapa 1 : Escrever o registro recebido no arquivo de registros.
    write_string_data(file_name, string_csv);

    // Etapa 2 : Guardar o rrn usado para escrever no arquivo grande e escrever o
    // próximo disponível no header.
    int rrn_usado = next_rrn();
    int next_rrn = rrn_usado + 1;
    FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");

    fseek(file_index_pointer, sizeof(int), SEEK_SET);
    fwrite(&next_rrn, sizeof(int), 1, file_index_pointer);


    // Etapa 3 : Escrever a chave primaria e o rrn usado para acessá-la no fim do arquivo de indices.
    // É a etapa em que salvamos um índice no arquivo de índices.
    fseek(file_index_pointer, 0, SEEK_END);
    fwrite(&key, sizeof(int), 1, file_index_pointer);
    fwrite(&rrn_usado, sizeof(int), 1, file_index_pointer);



    // Etapa 4 : Escrever a nova quantia de índices no arquivo de índices.
    int number_of_indexes = how_many_indexes() + 1;
    fseek(file_index_pointer, 0, SEEK_SET);
    fwrite(&number_of_indexes, sizeof(int), 1, file_index_pointer);

    fclose(file_index_pointer);

    // Etapa 5 : Re-ordenar o arquivo de índices a partir das chaves primarias.
    // Para isso, primeiro leremos todos os índices na RAM. Ordenaremos-os com o insertion
    // e escreveremos novamente.

    index_t *indexes = read_indexes_into_ram();
    sort_with_insertion(indexes);

    file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");

    fseek(file_index_pointer, SIZE_OF_INDEX_HEADER, SEEK_SET);
    int array_size = how_many_indexes();
    for (int i = 0; i < array_size; i++)
    {
        fwrite(&indexes[i].key, sizeof(int), 1, file_index_pointer);
        fwrite(&indexes[i].rrn, sizeof(int), 1, file_index_pointer);
    }

    fclose(file_index_pointer);


    free(indexes);


    return 1;
}

// TODO funcao acessada pela main que vai imprimir os dados buscados (obtidos
// por meio da funcao search_key_in_file)
unsigned short int search(char *file_name, int key)
{
    student_t *student = search_key_in_file(file_name, key);
    if (student == NULL)
    {
        return 0;
    }

    printf("-------------------------------\n");
    printf("USP number: %d\n", student -> usp_number);
    printf("Name: %s\n", student -> name);
    printf("Surname: %s\n", student -> surname);
    printf("Course: %s\n", student -> course);
    printf("Test grade: %.2f\n", student -> grade);
    printf("-------------------------------\n");
    free(student);

    return 1;
}

// Recebe o nome de um arquivo e um numero_usp como argumentos. Deleta o registro
// do estudante com determinado numero usp do arquivo, caso exista. Retorna 1 caso a remoção
// seja bem sucedida. 0 caso contrário.
unsigned short int delete_register(char *file_name, int key_to_delete)
{
    if (file_name == NULL)
    {
        return 0;
    }
    // Seguiremos as seguintes etapas para deletar um arquivo, por meio da remoção lógica:

    // Etapa 1 : Buscaremos o indice desse arquivo no arquivo de indices, por meio da chave primaria,
    // e com o seu rrn em mãos, sobrescreveremos-o no arquivo de registros com a string "|*".

    // Para remover o indice do arquivo de indice:

    // Etapa 2 : leremos os índices na RAM e trocaremos de posição o index a ser removido com o ultimo
    // (desorganizando os indices)

    // Etapa 3 : escreveremos no header que agora o arquivo de indices possui um indice a menos, e
    // ordenaremos novamente o vetor de indices até o numero de indices *escrito no header*
    // (visto que lidaremos a partir daqui como se o indice que agora está na ultima posicao do vetor
    // não existisse).

    // Etapa 4 : Armazenaremos o vetor de indices atualizado (sem a chave deletada) e ordenado
    // novamente no arquivo de índices.

    // Não alteraremos nada no proximo rrn disponível, visto que nada será efetivamente removido do
    // arquivo de registros grandes.

    // So... let's code it:

    // Etapa 1 : Buscaremos o indice desse arquivo no arquivo de indices, por meio da chave primaria,
    // e com o seu rrn em mãos, sobrescreveremos-o no arquivo de registros com a string "|*".
    index_t index = search_key(key_to_delete);

    // Caso de um registro não encontrado
    if (index.key == -1)
    {
        return 0;
    }

    FILE *file_pointer = fopen(file_name, "r+");
    // arquivo file_name não existe
    if (file_pointer == NULL)
    {
        return 0;
    }
    fseek(file_pointer, index.rrn * SIZE_OF_A_REGISTER, SEEK_SET);
    char buffer[] = "|*";
    fwrite(buffer, 1, strlen(buffer), file_pointer);

    fclose(file_pointer);

    // Etapa 2 : leremos os índices na RAM e "trocaremos de posição" o index a ser removido com o ultimo
    // (desorganizando os indices)
    // Para encontrar o indice da key a ser deletada, usaremos também busca binária, com uma função intermediaria
    // que faz essa busca para nós e retorna o indice da key encontrada. (Ou -1, caso não encontre)
    index_t *indexes = read_indexes_into_ram();

    int last_index = how_many_indexes() - 1;

    int index_in_array = binary_search_index(indexes, 0, last_index, key_to_delete);

    indexes[index_in_array].key = indexes[last_index].key;
    indexes[index_in_array].rrn = indexes[last_index].rrn;

    // Etapa 3: escreveremos no header que agora o arquivo de indices possui um indice a menos, e
    // ordenaremos novamente o vetor de indices até o numero de indices *escrito no header*
    FILE *index_file_pointer = fopen(FILE_OF_INDEX_NAME, "r+");
    assert(index_file_pointer != NULL);

    // Visto que last_index armazenava a quantia de index - 1 ... Não precisamos usar a funcao how_many novamente.
    fwrite(&last_index, 1, sizeof(int), index_file_pointer);
    fclose(index_file_pointer);

    sort_with_insertion(indexes);

    // Etapa 4 : Armazenaremos o vetor de indices atualizado (sem a chave deletada) e ordenado
    // novamente no arquivo de índices.
    FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");

    fseek(file_index_pointer, SIZE_OF_INDEX_HEADER, SEEK_SET);
    int array_size = last_index;
    for (int i = 0; i < array_size; i++)
    {
        fwrite(&indexes[i].key, sizeof(int), 1, file_index_pointer);
        fwrite(&indexes[i].rrn, sizeof(int), 1, file_index_pointer);
    }

    fclose(file_index_pointer);

    free(indexes);

    return 1;
}