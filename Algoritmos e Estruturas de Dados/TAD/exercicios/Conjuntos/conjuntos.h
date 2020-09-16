#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//  Define um tipo de variável contendo um conjunto de 0 a 99
typedef struct
{
    int vet[MAX];
} conjunto;

//  faz o conjunto vazio ser o valor para a variável conjunto A
conjunto* criar_conjunto();

//   toma os argumentos A e B que são conjuntos e retorna A U B à variável C
void uniao(conjunto *a, conjunto *b, conjunto *c);

// toma os argumentos A e B que são conjuntos e retorna A ^ B à variável C
void intersecao(conjunto *a, conjunto *b, conjunto *c);

//  toma os argumentos A e B que são conjuntos e retorna A - B à variável C
void diferenca(conjunto *a, conjunto *b, conjunto *c);

/*  toma o conjunto A e o objeto x cujo tipo é o tipo do elemento de A e 
    retorna um valor booleano – true se x pertence à A e false caso contrário   */
unsigned char membro(int x,conjunto *a);

/*  toma o conjunto A e o objeto x cujo tipo é o tipo do elemento de A e faz
    de x, um membro de A. O novo valor de A = A U {x}. Se x já é um membro de A, 
    então a operação insere não muda A   */
void inserir(int x,conjunto *a);

/*  remove o objeto x, cujo tipo é o tipo do elemento de A, de A. O novo valor 
    de A = A – {x}. Se x não pertence a A então a operação remove não altera A   */
void remover(int x, conjunto *a);

/*  Seta o valor da variável conjunto A = ao valor da variável conjunto B    */
void atribuir(conjunto *a, conjunto *b);

/*  retorna o valor mínimo no conjunto A. Por exemplo:
    Min({2,3,1}) = 1 e Min({‘a’,’b’,’c’}) = ‘a’    */
int min(conjunto *a);

/*  Similar a Min(A), mas retorna o máximo do conjunto    */
int max(conjunto *a);

/*  retorna true se e somente se os conjuntos A e B
    consistem dos mesmos elementos    */
unsigned char igual(conjunto *a, conjunto *b);

/*   libera memória usada por A     */
void liberar(conjunto *a);

/*   imprime elementos do conjunto A    */
void imprimir(conjunto *a);