/*  Projeto desenvolvido pelo aluno João Vitor Diógenes para a disciplina de
    algoritmos e estruturas de dados II, do curso Bacharelado em Sistemas de
    informação do Instituto de Ciências Matemáticas e de Computação (ICMC - USP).

    O projeto segue um padrão de nomenclatura de variáveis, funções, constantes/macros e afins
    em inglês, com comentários em português. Majoritariamente, o código busca ser auto-explicativo
    e com funcoes pequenas e intuitivas, sem a necessidade de códigos excessivos, valorizando a
    cultura "Keep it Simple".

    */

/*

    Entradas do exercício
Você receberá entradas diferentes para cada caso de teste, use a forma que achar melhor para lê-las.
Todas virão pela entrada padrão. As dispostas abaixo nunca mudarão para qualquer operação.

1ª Entrada[string] - Nome do arquivo binário
2ª Entrada[int] - Operação

As operações são:

1 - Exibição de todos os registros
2 - Exibição de metade dos registros, do começo ao meio
3 - Exibição de metade dos registros, do meio ao fim
4 - Exibição de uma faixa de registros
5 - Exibição de um registro específico
Para a operação 4, após o número da operação, você deverá ler os valores:

3ª Entrada[int] - Início da faixa(inclusive)
4ª Entrada[int] - Final da faixa(inclusive)
Para a operação 5:

3ª Entrada[int] - Posição do registro
Neste exercício estamos tratando a 'faixa' e o 'registro específico' como posições relativas dentro do arquivo binário,
ou seja: 1º registro; 2º registro; ... 10º registro. O número USP não passa de um valor numérico armazenado, futuramente
usaremos como chave primária. OBS: Caso o valor final da faixa supere o total de registros, exiba até o último disponível.
O run.codes aceitará tanto um arquivo .zip contendo o Makefile quanto apenas o arquivo .c. Recomendo que usem o Makefile.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filelib.h"

// funcao que retira o \n de uma string, caso haja algum
void sanitize_string(char *str);

int main(void)
{
    char file_name[SIZE_OF_STRINGS];
    fgets(file_name, sizeof(file_name), stdin);
    sanitize_string(file_name);

    unsigned short int operation = 0;
    scanf("%hu", &operation);

    unsigned short int size_of_list = 0;
    student_t *student_list = student_list_create(file_name, &size_of_list);
    if (student_list == NULL)
    {
        exit(1);
    }


    switch (operation)
    {
        case 1:
        {
            unsigned short int success = read_all_data(file_name, student_list, size_of_list);
            if (!success)
            {
                printf("Erro na execucao da operacao 1.\n");
                break;
            }

            success = print_data(student_list, size_of_list);
            if (!success)
            {
                printf("Erro na impressao da operacao 1.\n");
                break;
            }
            break;
        }

        case 2:
        {
            unsigned short int success = read_first_half(file_name, student_list, size_of_list);
            if (!success)
            {
                printf("Erro na execucao da operacao 2.\n");
                break;
            }

            success = print_data(student_list, size_of_list);
            if (!success)
            {
                printf("Erro na impressao da operacao 2.\n");
                break;
            }
            break;
        }
        case 3:
        {
            unsigned short int success = read_last_half(file_name, student_list, size_of_list);
            if (!success)
            {
                printf("Erro na execucao da operacao 3.\n");
                break;
            }

            success = print_data(student_list, size_of_list);
            if (!success)
            {
                printf("Erro na impressao da operacao 3.\n");
                break;
            }
            break;
        }
        case 4:
        {
            unsigned int initial_position = 0, final_position = 0;
            scanf("%u", &initial_position);
            scanf("%u", &final_position);

            unsigned short int success = read_specified_data(file_name, student_list, initial_position, final_position);
            if (!success)
            {
                printf("Erro na execucao da operacao 4.\n");
                break;
            }

            success = print_data(student_list, size_of_list);
            if (!success)
            {
                printf("Erro na impressao da operacao 4.\n");
                break;
            }
            break;
        }
        case 5:
        {
            unsigned int position = 0;
            scanf("%u", &position);

            unsigned short int success = read_single_data(file_name, student_list, position);
            if (!success)
            {
                printf("Erro na execucao da operacao 5.\n");
                break;
            }

            success = print_data(student_list, size_of_list);
            if (!success)
            {
                printf("Erro na impressao da operacao 5.\n");
                break;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    student_list_destroy(student_list);

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