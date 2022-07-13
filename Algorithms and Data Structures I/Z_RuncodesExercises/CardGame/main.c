#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pilha.h"

// Problema de: OBI - Olimpıada Brasileira de Informatica 2006 - Fase 1 Nivel 2.
// Disponıvel em: https://www.urionlinejudge.com.br/judge/pt/problems/view/2307

int inicia_rodada(pilha *compra, pilha *descarte);

int main()
{
    pilha compra, descarte, morto;
    pilha_cria(&compra);
    pilha_cria(&descarte);
    pilha_cria(&morto);

    //  Lendo a primeira entrada:   Numero de cartas da pilha de compras
    int num_cartas;
    scanf("%d", &num_cartas);

    //  Lendo as cartas a serem colocadas na pilha de compras na ordem em que serão retiradas
    for (int i = 0; i < num_cartas; i++)
    {
        int mini_buffer;
        scanf("%d", &mini_buffer);
        pilha_push(&compra, mini_buffer);
    }
    //  Invertendo a pilha (A primeira entrada lida deve ser a primeira a ser retirada,
    //  visto que essa foi a ordem de insercao, logo, ela deve estar no topo);
    pilha_inverte(&compra);

    int atual_morto = 0, num_rodadas = 1;

    //  Loop do joguinho rodando, em que cada carta retirada é um loop.
    while(1)
    {
        int mini_buffer;
        int prox_morto = atual_morto + 1;
        pilha_pop(&compra, &mini_buffer);
        //  Tiraremos uma carta da fila de compras e faremos algumas comparacoes.
        //  Se a carta tirada for o proximo da sequencia, ela irá para a pilha dos mortos,
        //  se for diferente, irá para a pilha de descarte.
        if (mini_buffer != prox_morto)
        {
            pilha_push(&descarte, mini_buffer);
        }
        else
        {
            pilha_push(&morto, mini_buffer);
            atual_morto++;
        }

        //  Se a ultima carta morta for igual ao numero de cartas, nosso jogo acabou
        //  e todas as cartas estão no morto
        if (atual_morto == num_cartas)
        {
            break;
        }
        //  Se não chegamos ao fim do jogo, verificamos se chegamos ao fim da pilha
        //  de compras para iniciar uma nova rodada e contabilizá-la.
        else if (pilha_is_empty(&compra))
        {
            inicia_rodada(&compra, &descarte);
            num_rodadas++;
        }
        //  Se nenhum condição for atendida, voltamos ao laço para ler puxar
        //  a próxima carta da pilha de compras
    }

    printf("%d\n", num_rodadas);

    pilha_destroy(&compra);
    pilha_destroy(&descarte);
    pilha_destroy(&morto);

    return 0;
}

int inicia_rodada(pilha *compra, pilha *descarte)
{
    //  O início da rodada se dá quando a pilha de compras é esvaziada
    //  e queremos que a pilha de descarte seja a nova pilha de compras
    if (pilha_is_empty(compra))
    {
        pilha_destroy(compra);
        *compra = *descarte;
        pilha_inverte(compra);
        pilha_cria(descarte);

        return 0;
    }
    else
    {
        return 1;
    }
}