#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void substituir(char str1[1000], char str2[30], char str3[30]);
void copia(char *str1, char *str2);

int main()
{

    char string1[1000], string2[30], string3[30];

    strcpy(string1, 
           "Atirei o pau no gato, mas o gato nao morreu. Dona chica fez alguma coisa e eu nao lembro o resto, mas e so um teste mesmo!");
    strcpy(string2, "gato");
    strcpy(string3, "cachorro");

    substituir(string1, string2, string3);

    printf("A string1, com a string %s sendo substituida pela string %s e:\n%s\n", string2, string3, string1);

    return 0;
}

void substituir(char str1[1000], char str2[30], char str3[30])
{
    for (int i = 0; i < strlen(str1); i++)       //  Primeiro laço, estamos procurando pelo char inicial de str2 em str1
    {
        char *backup;
        backup = (char *) calloc(1000, sizeof(char));
        
        int j = 0;                                  //  Ao encontrá-lo, é necessário tirar os caracteres de str2 em str1
        int match = 0;                              //  E fazer um "backup" dos demais caracteres da string
        if (str1[i] == str2[j])                     //  Para então, colocar a str3 concatenada, e depois retornar o resto da str1.
        {
            while (str1[i + j] == str2[j])
            {
                if ((j + 1) == strlen(str2))
                {
                    match = 1;
                }
                j++;
            }

            if (match == 1)
            {
                copia(&str1[i + j], backup);
                for (int k = i; k < strlen(str1); k++)  //  Limpando a str1 para concatenar a str2
                {
                    str1[k] = (char)NULL;
                }
                strcat(str1, str3);
                strcat(str1, backup);
            }
        }
        free(backup);
    }
    
}

void copia(char *str1, char *str2)  //  copia o que está na str1 para a str2 *void copia(*source, *destination);
{
    for (int i = 0; i < strlen(str1); i++)
    {
        str2[i] = str1[i];
    }
}