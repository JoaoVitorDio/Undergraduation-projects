#include <stdio.h>
#include <stdlib.h>

#define MAX1 100    //  Maximum lenght of string 1
#define MAX2 20     /*  Maximum lenght of string with error and
                        of the "correction" string */

/*      Descrição:

    É comum que ocorram erros de digitação em textos e, redigir o texto de maneira correta, exige certa
    atenção, podendo permanecer algumas ocorrências do erro que passem desapercebidas.
    Para resolver esse problema, escreva um programa que, dado um texto, possa substituir todas as
    ocorrências de um erro (caractere, ou de um grupo de caracteres) por uma correção (caractere, ou de um
    grupo de caracteres).

        Entrada
    A entrada possui vários casos de teste, com três linhas cada, e é terminada pelo final do arquivo
    (EOF). A primeira linha, de até 100 caracteres, é referente ao texto original com os erros de digitação.
    A segunda linha contém o erro a ser substituído. A terceira linha contém a correção. O erro e a correção
    poderão possuir até 20 caracteres cada.

        Saída
    Para cada caso de teste, imprima o texto da entrada com a devida correção aplicada. Caso o erro não
    exista no texto, imprima o texto original. Cada saída deverá possuir até 100 caracteres.

        Observações
    • Utilize um método próprio para a substituição de strings.
    • Pode ocorrer mais de uma substituição por texto.
    • Caso a saída exceda 100 caracteres, somente os 100 primeiros devem ser considerados.
    • Os textos, erros e correções podem ter caracteres especiais e números. */

int own_strlen(char *string)
{
    int size;
    for (int i = 0; ; i++)
    {
        if (string[i] == '\0')
        {
            size = i;
            break;
        }
    }
    return size;
}

void own_strcpy(char *destination, char *source)
{
    for (int i = 0; i <= own_strlen(source); i++)
    {
        destination[i] = source[i];
    }
}

void substitute(char *string1, char *string_error, char *string_correction)
{
    /*  First loop, searchig for the first character of string_error at main string
        If we need it, we'll start to compare all characters of both strings to see
        if the complete words are the same    */
    int size1 = own_strlen(string1);
    for (int i = 0; i < size1; i++)
    {
        if (string1[i] == string_error[0])
        {
            /*  Now that we have found the first character, we'll start our second loop,
                verifying if both strings are equal     */
            int size2 = own_strlen(string_error);

            int erro = 0;
            for (int k = 0; k < size2; k++)
            {
                if (string_error[k] != string1[k + i])
                {
                    erro = 1;
                    break;
                }
            }
            if (erro == 0)
            {
                char string_backup[MAX1];
                int size_error = own_strlen(string_error);
                int size_correction = own_strlen(string_correction);

                own_strcpy(string_backup, &string1[i + size_error]);
                own_strcpy(&string1[i], string_correction);

                own_strcpy(&string1[i + size_correction], string_backup);
            }
        }
    }
}

//  A function to fix the fgets catching \n from a string
void exclude_newline (char *string)
{
    int size = own_strlen(string);
    for (int i = 0; i < size; i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
}

int main()
{

    while (!feof(stdin))
    {
        char string1[MAX1];
        if (fgets(string1, sizeof(string1), stdin) == NULL)
        {
            break;
        }
        exclude_newline(string1);

        char string_error[MAX2];
        fgets(string_error, sizeof(string_error), stdin);
        exclude_newline(string_error);

        char string_correction[MAX2];
        fgets(string_correction, sizeof(string_correction), stdin);
        exclude_newline(string_correction);

        substitute(string1, string_error, string_correction);
        printf("%s\n", string1);
    }

    return 0;
}