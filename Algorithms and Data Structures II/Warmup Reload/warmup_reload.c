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


int main(void)
{
    char file_name[] = "registers_in_binary.bin";
    clean_old_data(file_name);

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

        // Armazenando uma string-linha contendo um registro em csv de um aluno no arquivo
        unsigned short int success = write_string_data(file_name, string_being_read);
        if (!success)
        {
            printf("Erro ao escrever a string %s no arquivo %s.\n", string_being_read, file_name);
        }
        
        free(string_being_read);
    }

    // Etapa de leitura do arquivo binário e impressão.
    unsigned short int size_of_list = 0;
    student_t *student_list = student_list_create(file_name, &size_of_list);
    if (student_list == NULL)
    {
        printf("Erro ao abrir o arquivo %s para leitura.\n", file_name);
        exit(1);
    }

    read_last_data(file_name, student_list);


    unsigned short int success = print_data(student_list, size_of_list);
    if (!success)
    {
        printf("Erro ao imprimir os dados lidos do binário.\n");
    }

    student_list_destroy(student_list);

    return 0;
}