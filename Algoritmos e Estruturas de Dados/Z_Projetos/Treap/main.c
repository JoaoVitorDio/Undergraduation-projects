/*  Projeto desenvolvido pelo aluno João Vitor Diógenes para a disciplina de
    algoritmos e estruturas de dados, do curso Bacharelado em Sistemas de
    informação do Instituto de Ciências Matemáticas e de Computação (ICMC - USP).

    O projeto segue um padrão de nomenclatura de variáveis, funções, constantes/macros e afins
    em inglês, com comentários em português. Majoritariamente, o código busca ser auto-explicativo,
    sem "constantes mágicas" e com funcoes pequenas e intuitivas, sem a necessidade de códigos
    excessivos, valorizando a cultura do e "Keep it Simple".

        Creditos quanto a elaboração do Problema:
    Professor Marcelo Garcia Manzato e alunos PAE Andre Zanon e Luan Souza.

        Arvores com Prioridades
        Descricao

    Este trabalho consiste na implementacao de uma arvore Treap (combinacao de Tree + Heap), que sao
    estruturas de dados balanceadas em que os nos contem uma chave e uma prioridade.
    As prioridades sao geradas aleatoriamente como uma forma de manter o balanceamento e as operacoes
    de insercao, remocao e busca em tempo de O(log(N)).
    Assim como arvores binarias, as treaps, mantem a mesma logica na qual nos com chaves maiores sao
    colocados a direita e nos com chaves menores sao colocados a esquerda. No entanto, o balanceamento e
    realizado conforme a prioridade dos mesmos.

    Para a operacao de remocao, deve-se fazer com que o no a ser removido vire
    uma folha ou semi-folha, logo, para que isso aconteca e a estrutura mantenha-se a mesma, as rotacoes
    deverao manter um mesmo sentido, assim, seu programa ira rotacionar sempre
    somente para a esquerda, ate o no a ser removido vire uma folha. Ja para a operacao de
    insercao, assim como na Figura 2, deve seguir uma Max Heap, em que nos com maior valor sao
    priorizados.

    A implementacao da sua Treap dever a conter as seguintes operacoes:
    • Insercao de um numero, em O(log(N))
    • Busca de um numero, em O(log(N))
    • Remocao de um numero, em O(log(N))
    • Impressao da arvore em-ordem, pos-ordem, pre-ordem ou em largura, em O(N)

        Entradas
    Seu programa deve ler um conjunto de valores da entrada padrao. A entrada contem um conjunto de
    n linhas, seguidas por respectivas n operacoes. Cada linha e formatada da seguinte maneira:
    • insercao chave prioridade, em que tanto chave quanto prioridade sao numeros.
    • remocao chave prioridade, em que tanto chave quanto prioridade sao numeros.
    • buscar chave em que dever a ser retornado se existe ou nao um numero na arvore. Caso exista o
    retorno ser a 1, caso contrario 0.
    • impressao modo em que dever a ser impressa a arvore conforme o modo especificado. Os modos
    podem ser ordem; posordem; preordem e largura.

        Saidas
    Seu programa deve imprimir as linhas correspondentes para cada operacao, se necessario. Para
    insercao, quando a chave ja existir dever a ser impresso a frase ”Elemento ja existente”, ja quando a
    chave nao existe para a remocao, devera ser impresso ”Chave nao localizada”.
    A impressao de cada no deve ser realizada como uma tupla, logo, no formato (info, prio) no qual,
    info representa a chave e prio a prioridade do no.

        Entradas
    10
    insercao 30 5
    insercao 20 2
    insercao 40 4
    insercao 70 10
    insercao 50 15
    insercao 20 18
    impressao preordem
    impressao largura
    remocao 50
    impressao ordem

        Saidas
    Elemento ja existente
    (50, 15) (30, 5) (20, 2) (40, 4) (70, 10)
    (50, 15) (30, 5) (70, 10) (20, 2) (40, 4)
    (20, 2) (30, 5) (40, 4) (70, 10)
    */

#include "treap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_OF_OP 10 // Tamanho da maior string necessária para armazenar o nome das operacoes
#define SIZE_OF_MODE 9

int main()
{
    unsigned short int num_op = 0;
    scanf("%hu", &num_op);

    treap_t *treap = treap_create();

    for (int i = 0; i < num_op; i++)
    {
        char operation[SIZE_OF_OP];
        scanf("%s ", operation);

        if (strcmp(operation, "insercao") == 0)
        {
            int key = 0, priority = 0;
            scanf("%d %d", &key, &priority);
            unsigned short int success = treap_insert(treap, key, priority);
            if (!success)
            {
                printf("Elemento ja existente\n");
            }
        }
        else if (strcmp(operation, "remocao") == 0)
        {
            int key = 0;
            scanf("%d", &key);
            unsigned short int success = treap_remove(treap, key);
            if (!success)
            {
                printf("Chave nao localizada\n");
            }
        }
        else if (strcmp(operation, "buscar") == 0)
        {
            int key = 0;
            scanf("%d", &key);
            unsigned short int success = treap_search(treap, key);
            if (success == 1)
            {
                printf("1\n");
            }
            else
            {
                printf("0\n");
            }
        }
        else if (strcmp(operation, "impressao") == 0)
        {
            char mode[SIZE_OF_MODE];
            scanf("%s", mode);
            if (strcmp(mode, "ordem") == 0)
            {
                treap_inorder(treap);
            }
            else if (strcmp(mode, "posordem") == 0)
            {
                treap_postorder(treap);
            }
            else if (strcmp(mode, "preordem") == 0)
            {
                treap_preorder(treap);
            }
            else if (strcmp(mode, "largura") == 0)
            {
                treap_breadth_first(treap);
            }
            else
            {
                printf("Uso da funcao impressao: impressao modo_de_impressao\n");
            }
        }
        else
        {
            printf("CONJUNTO DE OPERACOES E USO:\ninsercao chave prioridade\n");
            printf("remocao chave prioridade\nbusca chave\nimpressao modo\n\n");
        }

    }
    treap_destroy(treap);

    return 0;
}
