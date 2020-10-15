/*
    Estagiarios PAE que elaboraram o problema: Andre Zanon e Luan Souza

    Mudam-se os Tempos, Mudam-se as Filas

    ------- Descricao
    Durante a pandemia do coronavırus, varios estabelecimentos comerciais precisaram repensar como
    organizam suas filas de forma a atender todos os clientes de maneira eficiente, mas priorizando os grupos
    de risco. Nesse sentido, voce foi designado como desenvolvedor da estrutura de dados gerenciadora, uma
    fila de prioridade, que sera responsavel por organizar os consumidores com um criterio justo.
    Cada pessoa da fila sera caracterizada por seu nome, idade e se a mesma possui ou nao uma condicao de
    saude agravante para a COVID 19 como, por exemplo, diabetes, asma e pneumonia. Assim, a prioridade
    na fila segue os seguintes criterios, de maneira decrescente:
    1. Pessoas idosas (igual ou acima de 60 anos pela constituicao brasileira) e com condicao agravante
    de saude;
    2. Pessoas com condicao agravante de saúde;
    3. Pessoas idosas;
    4. Pessoas não idosas e sem condições agravante de saúde.

    Com isso, caso uma fila possua somente pessoas do publico 4, por exemplo, seu funcionamento seguira
    o First In First Out (FIFO), ou seja, a primeira pessoa que entrou na fila sera a primeira a ser atendida.
    Entretanto, caso alguma pessoa de um outro grupo mais prioritario entre na fila, ela passara na frente de
    todos os outros com menor prioridade, de forma com que o contato desta com as outras seja minimizado.
    Caso pessoas do mesmo grupo entrem na fila, a ordem segue o FIFO, portanto, se duas do grupo 1
    entrarem na fila elas irão ser as primeiras da fila, mas a que entrou antes é a que sera atendida.

    ------- Entradas
    A entrada contém um unico conjunto de teste. A primeira linha da entrada contém um inteiro N que
    indica quantas ações foram feitas na fila (1 <= N <= 100) e as proximas N linhas seguirão o formato de
    ação e parametros, quando necessario. As ações são:
    • ENTRA, em que serão passados como parametro o nome inicial da pessoa, sua idade e se possui
    alguma condição de saúde (1 se sim e 0 caso contrario). Se a fila estiver cheia deve ser mostrado
    ”FILA CHEIA” como saıda.
    • SAI, em que a proxima pessoa da fila e atendida e consequentemente removida da fila. Caso a fila
    esteja vazia deve ser mostrado ”FILA VAZIA” como saıda.

    ------- Saídas
    Para cada comando ”SAI” da fila deve ser mostrado o nome, idade e condição de saúde da proxima
    pessoa a ser atendida.

    -------- Observações
    • O uso de fila e obrigatorio.
    • Somente as bibliotecas stdio.h, stdlib.h e string.h podem ser utilizadas.

    -------- Exemplo
        Entrada
    10
    SAI
    ENTRA Maria 26 0
    ENTRA Pedro 25 0
    SAI
    ENTRA Josefina 64 1
    SAI
    ENTRA Silva 63 0
    ENTRA Leticia 15 1
    SAI
    SAI
        Saída
    FILA VAZIA
    Maria 26 0
    Josefina 64 1
    Leticia 15 1
    Silva 63 0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

//  Importante lembrar que as entradas do run.codes são controladas e automáticas,
//  então não precisamos nos preocupar com as entradas do usuário.

#define BUF_SIZE 50
#define TERCEIRA_IDADE 60

typedef struct
{
    char nome[30];
    unsigned short int idade, agravante;
}   paciente;

void exclude_newline(char *string);

int main()
{
    fila_t *idosos_e_risco, *risco, *idosos, *comum;
    idosos_e_risco = criar();
    risco = criar();
    idosos = criar();
    comum = criar();

    int count;
    if (scanf("%d\n", &count) == EOF)
    {
        return 0;
    }
    setbuf(stdin, NULL);

    int pessoas_na_fila = 0;

    for (int i = 0; i < count; i++)
    {
        //  Lendo a entrada do usuário e armazenando em um buffer para sanitizar
        //  e separar/armazenar nas diferentes variáveis que precisamos.
        char buffer[BUF_SIZE];
        if (fgets(buffer, BUF_SIZE, stdin) == NULL)
            return 0;
        exclude_newline(buffer);

        //  buffer usado para separar a string lida
        char *inner_buff;
        inner_buff = strtok(buffer, " \\\n");

        char controller[6];
        strcpy(controller, inner_buff);

        if (strcmp(controller, "SAI") == 0)
        {
            //  Usando um ponteiro para receber o endereço de memória em que
            //  os dados do paciente removido da fila estão
            paciente *node = NULL;

            if (pessoas_na_fila == 0)
            {
                printf("FILA VAZIA\n");
            }
            else
            {
                if (!isEmpty(idosos_e_risco))
                {
                    remover(idosos_e_risco, (void *)&node);
                    pessoas_na_fila--;
                }
                else if (!isEmpty(risco))
                {
                    remover(risco, (void *)&node);
                    pessoas_na_fila--;
                }
                else if (!isEmpty(idosos))
                {
                    remover(idosos, (void *)&node);
                    pessoas_na_fila--;
                }
                else
                {
                    remover(comum, (void *)&node);
                    pessoas_na_fila--;
                }
                printf("%s %hu %hu\n", node -> nome, node -> idade, node -> agravante);
                free(node);
            }
        }
        else
        {
            //  p é um paciente de buffer. Usaremos-o temporariamente apenas para
            //  armazenar os dados e inseri-lo na fila
            paciente *p = (paciente *) calloc(1, sizeof(paciente));
            inner_buff = strtok(NULL, " ");
            if (inner_buff == NULL)
                return 0;

            strcpy(p -> nome, inner_buff);

            inner_buff = strtok(NULL, " ");
            if (inner_buff == NULL)
                return 0;

            p -> idade = atoi(inner_buff);

            inner_buff = strtok(NULL, " ");
            if (inner_buff == NULL)
                return 0;

            p -> agravante = atoi(inner_buff);

            if ((p -> idade) >= TERCEIRA_IDADE && (p -> agravante) == 1)
            {
                inserir(idosos_e_risco, p);
            }
            else if (p -> agravante == 1)
            {
                inserir(risco, p);
            }
            else if (p -> idade >= 60)
            {
                inserir(idosos, p);
            }
            else
            {
                inserir(comum, p);
            }

            pessoas_na_fila++;
        }
    }

    while (pessoas_na_fila > 0)
    {
        paciente *node = NULL;
        if (!isEmpty(idosos_e_risco))
        {
            remover(idosos_e_risco, (void *)&node);
            pessoas_na_fila--;
        }
        else if (!isEmpty(risco))
        {
            remover(risco, (void *)&node);
            pessoas_na_fila--;
        }
        else if (!isEmpty(idosos))
        {
            remover(idosos, (void *)&node);
            pessoas_na_fila--;
        }
        else
        {
            remover(comum, (void *)&node);
            pessoas_na_fila--;
        }
        free(node);
    }


    destruir(idosos_e_risco);
    destruir(risco);
    destruir(idosos);
    destruir(comum);

    return 0;
}

void exclude_newline (char *string)
{
    int size = strlen(string);
    for (int i = 0; i < size; i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
}