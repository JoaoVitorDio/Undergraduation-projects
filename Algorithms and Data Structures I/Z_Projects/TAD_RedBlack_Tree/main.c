/*  Projeto desenvolvido pelo aluno João Vitor Diógenes para a disciplina de
    algoritmos e estruturas de dados, do curso Bacharelado em Sistemas de
    informação do Instituto de Ciências Matemáticas e de Computação (ICMC - USP).

    O projeto segue um padrão de nomenclatura de variáveis, funções, constantes/macros e afins
    em inglês, com comentários em português. Majoritariamente, o código busca ser auto-explicativo,
    sem "constantes mágicas" e com funcoes pequenas e intuitivas, sem a necessidade de códigos
    excessivos, valorizando a cultura do e "Keep it Simple".

        Creditos quanto a elaboração do Problema:
    Professor Marcelo Garcia Manzato e alunos PAE Andre Zanon e Luan Souza

        Arvores Balanceadas
        Descricao
    Neste projeto voce deve implementar a arvore LLRB(Left-Leaning Red–Black). A sua implementacao
    deve ter as seguintes operacoes:

    • Insercao de um numero inteiro na arvore balanceada em O(log n)
    • Sucessor de uma chave em O(log n)
    • Predecessor de uma chave O(log n)
    • Maximo O(log n)
    • Minimo O(log n)
    • Impressao pre-ordem,em-ordem e pos-ordem em O(n)
    • Inicializacao de uma arvore balanceada em O(1)
    • Desalocacao da arvore em O(n)

    Note que remocao de um unico elemento nao faz parte do conjunto obrigatorio de operacoes, com a
    finalidade de simplificar o projeto.


        Entrada
    A entrada deve ser lida da entrada padrao e tem o seguinte formato:
    A primeira linha contem o numero de operacoes N. As proximas N linhas contem as operacoes, uma por
    linha. As operacoes possuem o seguinte formato:
    O X
    No qual, O pode assumir 1 para insercao, 2 para sucessor, 3 para predecessor, 4 para maximo,
    5 para minimo, 6 para impressao pre-ordem, 7 para impressao em-ordem e 8 para impressao
    pos-ordem. Utilize as operacoes de inicializacao e desalocacao da arvore no inicio e final da execucao,
    respectivamente. X e um valor inteiro e ocorre nas opcoes 1 (insercao), 2 (sucessor) e 3 (predecessor)
    apenas.

        Saida
    Para a operacao 1 (insercao) nao imprima nada na tela. Para as operacoes 2 (sucessor), 3 (predecessor),
    4 (maximo) e 5 (minimo) imprima um unico numero inteiro com a resposta em uma linha em separado.
    Para as operacoes 6 (impressao pre-ordem), 7 (em-ordem) e 8 (pos-ordem), imprima uma sequencia de
    numeros inteiros separados com um unico espaco em branco entre numeros e em uma linha em separado.
    Para respostas a consultas invalidas, imprima a mensagem “erro” em uma linha em separado.

        Observacoes
    • O uso da estrutura arvore e obrigatorio;
    • Somente as bibliotecas stdio.h, stdlib.h e string.h podem ser utilizadas.

        Exemplo
    Entradas
    10
    1 5
    1 4
    1 3
    1 2
    1 1
    3 1
    2 1
    4
    5
    7
        Saidas
    2
    erro
    5
    1
    1 2 3 4 5

    */

#include <stdio.h>
#include <stdlib.h>
#include "redblack.h"

int main()
{

    unsigned short int num_op = 0;
    scanf("%hu", &num_op);

    redblack_t *redblack = redblack_create();

    for (int i = 0; i < num_op; i++)
    {
        int operation = 0;
        scanf("%d", &operation);
        switch (operation)
        {
            case 1: // insercao
            {
                int number = 0, success = 0;
                scanf(" %d", &number);
                success = redblack_insert(redblack, number);
                if (!success)
                {
                    printf("erro\n");
                }
                break;
            }
            case 2: // sucessor
            {
                int number = 0, success = 0, successor = 0;
                scanf(" %d", &number);
                success = redblack_successor(redblack, number, &successor);
                if (!success)
                {
                    printf("erro\n");
                }
                else
                {
                    printf("%d\n", successor);
                }
                break;
            }
            case 3: // predecessor
            {
                int number = 0, success = 0, predecessor = 0;
                scanf(" %d", &number);
                success = redblack_predecessor(redblack, number, &predecessor);
                if (!success)
                {
                    printf("erro\n");
                }
                else
                {
                    printf("%d\n", predecessor);
                }
                break;
            }
            case 4: // máximo
            {
                // desde que a arvore nao esteja vazia, a função
                // maxima sempre será bem sucedida.
                int max = 0;
                max = redblack_max(redblack);
                printf("%d\n", max);
                break;
            }
            case 5: // mínimo
            {
                // desde que a arvore nao esteja vazia, a função
                // minimo sempre será bem sucedida.
                int min = 0;
                min = redblack_min(redblack);
                printf("%d\n", min);
                break;
            }
            case 6: // impressão pré-ordem
            {
                redblack_preorder(redblack);
                break;
            }
            case 7: // impressão em-ordem
            {
                redblack_inorder(redblack);
                break;
            }
            case 8: // impressão pós-ordem
            {
                redblack_postorder(redblack);
                break;
            }
        }
    }

    redblack_destroy(redblack);

    return 0;
}