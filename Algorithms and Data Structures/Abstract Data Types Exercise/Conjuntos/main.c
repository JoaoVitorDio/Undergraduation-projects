#include "conjuntos.h"

/*  Implemente em C o TAD conjunto de números inteiros

    Implemente um programa cliente que utilize ao menos 4 das
    funções do TAD

    Implemente um Makefile para seu programa  */

int main()
{
    conjunto *a, *b, *c;

    a = criar_conjunto();
    b = criar_conjunto();
    c = criar_conjunto();

    inserir(5, a);
    inserir(10, a);

    inserir(5, b);
    inserir(17, b);

    uniao(a, b, c);
    printf("Elementos do conjunto C (A U B):\n");
    imprimir(c);

    intersecao(a, b, c);
    printf("Elementos do conjunto C (A ^ B):\n");
    imprimir(c);

    int minimo = min(a);
    printf("min(a) = %d\n", minimo);

    minimo = max(a);
    printf("max(a) = %d\n", minimo);

    printf("Elementos do conjunto B:\n");
    imprimir(b);
    remover(17, b);
    printf("Elementos do conjunto B (após remover o 17):\n");
    imprimir(b);

    liberar(a);
    liberar(b);
    liberar(c);
}
