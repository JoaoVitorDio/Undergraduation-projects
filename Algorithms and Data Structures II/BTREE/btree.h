/*
    Adaptado do código de:
    Henrique Gomes Zanin
    Gabriel Guimaraes Vilas Boas Marin
*/

#ifndef __BTREE__
#define __BTREE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "generaldata.h"

#define PAGESIZE 4096
#define TREE_HEADER PAGESIZE
#define MAXKEYS 203
#define AUX_FIELDS_SIZE_ON_PAGE (2 + 1 + 8)
// Contador de chaves, o booleano "is_leaf" e rrn da propria pagina
#define FREE_SPACE_ON_PAGE PAGESIZE - ((MAXKEYS * 12) + ((MAXKEYS + 1) * 8) + AUX_FIELDS_SIZE_ON_PAGE)
                            // 4096 - 4079 = 17
#define SIZE_OF_RECORD ( sizeof(int) + sizeof(long) )

typedef struct record {
    int key;
    long recordRRN;
}   record;

typedef struct page {
    record *records;
    long *childs;
    short numberOfKeys;
    char isLeaf;
    // necessario adicionar esse campo para manter um tracking do rrn das paginas
    // e conseguir setar as chaves promovidas para as filhas no split
    long pageRRN;
}   btPage;

typedef struct promotedKey {
    int key;
    long recordRRN;
    long childs[2];
}   promotedKey;

void printPageNode(btPage *root);

// Recebe como argumento um arquivo "de indexes" vazio ou contendo uma btree
// e retorna a pagina da btree que contem a raiz, ou cria uma e a retorna
btPage *pegaOuCriaRaiz(FILE *fp);

// Recebe como argumento o arquivo da arvore B e retorna a sua raiz, caso ja
// tenha sido criada.
btPage *pegaRaiz(FILE *fp);

// Insercao de um registro na arvore B. Recebe como argumento o endereco de
// uma estrutura record (um indice), // A pagina a ser recebida eh a da raiz.
// O arquivo eh o da arvore B / indices
unsigned short int insercaoArvore(record *newRecord, btPage **root, FILE *fp);

// Returns rrn if key exist, else return -1
// Partimos do ponto que, o uso na main ja esta chamando essa funcao,
// enviando a pagina da raiz como node
long buscaArvore(btPage *node, int key, FILE *fp);

// Funcao usada para liberar uma pagina lida na RAM, usada na main
// para liberar a raiz
void libera_node(btPage *root);

#endif