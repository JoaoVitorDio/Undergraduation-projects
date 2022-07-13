#include "pilha.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// string[strcspn(string, "\n")] = '\0';   Retirando \n da string lida por fgets
// Programa que verifica se todas as chaves, colchetes e parenteses abertos
// foram fechados. (Exercício de ALGED usando pilhas)

#define MAXSTRING 100

int compara(char *c1, char *c2)
{
    if (*c1 == '{')
    {
        if (*c2 == '}')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (*c1 == '[')
    {
        if (*c2 == ']')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (*c2 == ')')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int main()
{
    pilha_t *p = create();


    char string[MAXSTRING];
    printf("Digite uma sequencia de caracteres.\n");
    fgets(string, MAXSTRING, stdin);
    string[strcspn(string, "\n")] = '\0';

    int size_string = strlen(string);
    for (int i = 0; i < size_string; i++)
    {
        if (string[i] == '{' || string[i] == '[' || string[i] == '(')
        {
            push(p, &string[i]);
        }
        else if (string[i] == '}' || string[i] == ']' || string[i] == ')')
        {
            char *character;
            if(pop(p, (void **)&character) == -1)
            {
                printf("Há erros na sequencia (Mais expressoes fechadas que abertas).\n");
                return 0;
            }

            if (!compara(character, &string[i]))
            {
                printf("Há erros na sequencia (Alguma expressao esta na ordem errada).\n");
                printf("Expressao atual: '%c'. Expressao de fechamento recebida: '%c'\n", *character, string[i]);
                return 0;
            }
        }
    }

    if (isEmpty(p))
    {
        printf("A sequencia esta correta.\n");
    }
    else
    {
        printf("Há erros na sequencia. Mais expressoes abertas que fechadas.\n");
    }

    destroy(p);

    return 0;
}