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


    // Na remoção por pilha, lidaremos com 2 casos.
    // Caso 1: Há registros já deletados e iremos sobrescrever no mesmo rrn de algum arquivo deletado.
    // caso 2: Não há nenhum registro e utilizaremos a função de inserção "comum", já utilizada enquanto
    // lidávamos apenas com inserção lógica.

    // Lidando com o caso 1, se for ele:
    // Etapa 1: Lermos do header do arquivo de deletados qual o último arquivo deletado, se houver algum,
    //          para que usemos o seu rrn na inserção.
    // Etapa 2: Inserimos o registro no arquivo de registros, no rrn que pegamos do arquivo de índice.
    // Etapa 3: Atualizamos o header do arquivo de deletados, já que agora a pilha descerá um nível,
    //          por já termos utilizado um dos campos deletados.
    // Etapa 4: Inserimos o novo indice no arquivo de indices.
    // Etapa 5: Atualizamos o header do arquivo de indices.
    // Etapa 6: Re-ordenamos o arquivo de índices.
    FILE *deleted_fp = fopen(FILE_OF_DELETED, "r+");

    // Verificando assim como na deleção, se o arquivo já foi inicializado. Se não, pulamos direto para o caso 2
    int case_flag = 0, rrn_to_use_in_register_file = 0;
    if (!feof(deleted_fp))
    {
        int valid_deleted_rrn = 0;
        fread(&valid_deleted_rrn, 1, sizeof(valid_deleted_rrn), deleted_fp);
        // Garantindo que não escreveremos nada no header rsrs
        if (valid_deleted_rrn > 0)
        {

            case_flag = 1;
            // Etapa 1: Lermos do header do arquivo de deletados qual o último arquivo deletado, se houver algum,
            // para que usemos o seu rrn na inserção.
            fseek(deleted_fp, valid_deleted_rrn * SIZE_OF_RRN, SEEK_SET);
            fread(&rrn_to_use_in_register_file, SIZE_OF_RRN, 1, deleted_fp);

            // Etapa 2: Inserimos o registro no arquivo de registros, no rrn que pegamos do arquivo de índice.
            FILE *register_fp = fopen(file_name, "r+");
            fseek(register_fp, rrn_to_use_in_register_file * SIZE_OF_A_REGISTER, SEEK_SET);
            assert(write_string_data(register_fp, string_csv) != 0);
            fclose(register_fp);

            // Etapa 3: Atualizamos o header do arquivo de deletados, já que agora a pilha descerá um nível,
            // por já termos utilizado um dos campos deletados.
            fseek(deleted_fp, 0, SEEK_SET);
            valid_deleted_rrn--;
            fwrite(&valid_deleted_rrn, 1, sizeof(valid_deleted_rrn), deleted_fp);

            // Etapa 4: Escrever a chave primaria e o rrn usado para acessá-la no fim do arquivo de indices.
            // É a etapa em que salvamos um índice no arquivo de índices.

            // Precisamos saber qual o numero de indices para que coloquemos o novo indice não no fim do arquivo,
            // mas sim, na próxima posição além do último índice que estamos considerando. Visto que a operação de
            // literalmente apagar um dado de um arquivo praticamente inexiste, nós apenas sobrescrevemos os dados no
            // arquivo de indices, de forma que, o fim "físico" dele não necessariamente corresponde mais ao último
            // dos nossos índices.
            int num_of_indexes = how_many_indexes();
            FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");
            fseek(file_index_pointer, SIZE_OF_INDEX_HEADER + num_of_indexes * SIZE_OF_A_INDEX, SEEK_SET);
            fwrite(&key, sizeof(int), 1, file_index_pointer);
            fwrite(&rrn_to_use_in_register_file, sizeof(int), 1, file_index_pointer);
            fclose(file_index_pointer);
        }
        else
        {
            case_flag = 2;
        }
    }
    else
    {
        case_flag = 2;
    }

    fclose(deleted_fp);



    // Lidando com o caso 2:

    // Etapa 1 : Escrever o registro recebido no arquivo de registros.
    // Etapa 2 : Guardar o rrn usado para escrever no arquivo grande e escrever o
    //           próximo rrn disponível no header, preparando para a próxima inserção.
    // Etapa 3 : Escrever a chave primaria e o rrn usado para acessá-la no fim do arquivo de indices.
    // Etapa 4 : Escrever a nova quantia de índices no arquivo de índices.
    // Etapa 5 : Re-ordenar o arquivo de índices a partir das chaves primarias. E reescrever os índices
    //           no arquivo de índice.

    // Etapa 1 : Escrever o registro recebido no arquivo de registros. Basta escrever no fim.
    if (case_flag == 2)
    {
        FILE *file = fopen(file_name, "r+");
        fseek(file, 0, SEEK_END);
        write_string_data(file, string_csv);
        fclose(file);

        // Etapa 2 : Guardar o rrn usado para escrever no arquivo grande e escrever o
        // próximo disponível no header.
        int rrn_usado = next_rrn();
        int next_rrn = rrn_usado + 1;
        FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");

        fseek(file_index_pointer, sizeof(int), SEEK_SET);
        fwrite(&next_rrn, sizeof(int), 1, file_index_pointer);


        // Etapa 3 : Escrever a chave primaria e o rrn usado para acessá-la no fim do arquivo de indices.
        // É a etapa em que salvamos um índice no arquivo de índices.

        // Precisamos saber qual o numero de indices para que coloquemos o novo indice não no fim do arquivo,
        // mas sim, na próxima posição além do último índice que estamos considerando. Visto que a operação de
        // literalmente apagar um dado de um arquivo praticamente inexiste, nós apenas sobrescrevemos os dados no
        // arquivo de indices, de forma que, o fim "físico" dele não necessariamente corresponde mais ao último
        // dos nossos índices.
        int num_of_indexes = how_many_indexes();
        fseek(file_index_pointer, SIZE_OF_INDEX_HEADER + num_of_indexes * SIZE_OF_A_INDEX, SEEK_SET);
        fwrite(&key, sizeof(int), 1, file_index_pointer);
        fwrite(&rrn_usado, sizeof(int), 1, file_index_pointer);

        fclose(file_index_pointer);
    }



    // Etapa 4 : Escrever a nova quantia de índices no arquivo de índices.
    FILE *file_index_pointer = fopen(FILE_OF_INDEX_NAME, "r+");
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

    // Etapa 5: Para a remoção por pilha, colocaremos o rrn do registro apagado em um novo arquivo
    // stack_rrn para que a inserção possa sobrescrevê-lo.

    // So... let's code it:

    // Etapa 1 : Buscaremos o indice desse arquivo no arquivo de indices, por meio da chave primaria,
    // e com o seu rrn em mãos, sobrescreveremos-o no arquivo de registros com a string "|*".
    index_t index = search_key(key_to_delete);

    // Caso de um registro não encontrado
    if (index.key == -1)
    {
        return 0;
    }

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

    // Etapa 5: Para a remoção por pilha, colocaremos o rrn do registro apagado em um novo arquivo
    // deleted.bin para que a inserção possa sobrescrevê-lo. Atualizaremos o header do arquivo deleted
    // para que ele esteja apontando para o ultimo deletado.
    FILE *deleted_fp = fopen(FILE_OF_DELETED, "r+");

    // Verificando se o arquivo de deletados já foi usado alguma vez e já possui header ou teremos
    // de inicializá-lo. Estou fazendo isso no código da própria função apenas por ser pequeno.
    fseek(deleted_fp, 0, SEEK_END);
    int aux = ftell(deleted_fp);
    if (aux == 0) fwrite(&aux, 1, sizeof(int), deleted_fp);
    fseek(deleted_fp, 0, SEEK_SET);

    // Armazenando o rrn do registro apagado no arquivo de deletados
    int valid_deleted_rrn = 0;
    fread(&valid_deleted_rrn, 1, sizeof(valid_deleted_rrn), deleted_fp);

    // Soma-se o valor de RRN para pular o header.
    fseek(deleted_fp, SIZE_OF_RRN + valid_deleted_rrn * SIZE_OF_RRN, SEEK_SET);
    fwrite(&index.rrn, 1, sizeof(index.rrn), deleted_fp);

    // Atualizando o header do arquivo deleted para que ele esteja apontando para o ultimo deletado.
    fseek(deleted_fp, 0, SEEK_SET);
    valid_deleted_rrn++;
    fwrite(&valid_deleted_rrn, 1, sizeof(valid_deleted_rrn), deleted_fp);

    fclose(deleted_fp);

    return 1;
}

// Imprime todos os registros do arquivo de registros passado como argumento, independentemente
// de terem sido removidos logicamente ou não.
unsigned short int sequential_print(char *file_name)
{
    FILE *file_pointer = fopen(file_name, "r+");
    if (file_pointer == NULL)
    {
        return 0;
    }

    while (1)
    {
        student_t student;
        unsigned short int success = read_register(&student, file_pointer);
        if (!success)
        {
            break;
        }
        printf("-------------------------------\n");
        printf("USP number: %d\n", student.usp_number);
        printf("Name: %s\n", student.name);
        printf("Surname: %s\n", student.surname);
        printf("Course: %s\n", student.course);
        printf("Test grade: %.2f\n", student.grade);
        printf("-------------------------------\n");
    }

    fclose(file_pointer);

    return 1;
}