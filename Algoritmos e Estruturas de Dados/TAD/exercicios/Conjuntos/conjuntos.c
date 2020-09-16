#include "conjuntos.h"

conjunto* criar_conjunto()
{
    conjunto *a = (conjunto *) calloc(1, sizeof(conjunto));
    return a;
}

void uniao(conjunto *a, conjunto *b, conjunto *c)
{
    for (int i = 0; i < MAX; i++)
    {
        c -> vet[i] = 0;
        if ((a -> vet[i] == 1) || (b -> vet[i] == 1))
        {
            c -> vet[i] = 1;
        }
    }
}

void intersecao(conjunto *a, conjunto *b, conjunto *c)
{
    for (int i = 0; i < MAX; i++)
    {
        c -> vet[i] = 0;
        if ((a -> vet[i] == 1) && (b -> vet[i] == 1))
        {
            c -> vet[i] = 1;
        }
    }
}

void diferenca(conjunto *a, conjunto *b, conjunto *c)
{
    for (int i = 0; i < MAX; i++)
    {
        if ((a -> vet[i] == 1) && (b -> vet[i] == 0))
        {
            c -> vet[i] = 1;
        }
    }
}

unsigned char membro(int x, conjunto *a)
{
    if (a -> vet[x] == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void inserir(int x, conjunto *a)
{
    a -> vet[x] = 1;
}

void remover(int x, conjunto *a)
{
    a -> vet[x] = 0;
}

void atribuir(conjunto *a, conjunto *b)
{
    for (int i = 0; i < MAX; i++)
    {
        a -> vet[i] = b -> vet[i];
    }
}

int min(conjunto *a)
{
    for (int i = 0; i < MAX; i++)
    {
        if (a -> vet[i] == 1)
        {
            return i;
        }
    }
    return 0;
}

int max(conjunto *a)
{
    for (int i = MAX - 1; i >= 0; i--)
    {
        if (a -> vet[i] == 1)
        {
            return i;
        }
    }
    return 0;
}

unsigned char igual(conjunto *a, conjunto *b)
{
    for (int i = 0; i < MAX; i++)
    {
        if (a -> vet[i] != b -> vet[i])
        {
            return 0;
        }
    }
    return 1;
}


void liberar(conjunto *a)
{
    free (a);
}

void imprimir(conjunto *a)
{
    for (int i = 0; i < MAX; i++)
    {
        if (a -> vet[i] == 1)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}

