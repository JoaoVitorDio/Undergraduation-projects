#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "dictionary.h"

/*  Esse TAD dictionary se utiliza da estrutura de dados "skiplist".
    Seria possível fazer outro TAD para a skiplist, utilizando ponteiros
    void e usar esse TAD de maneira mais abstraída, adaptando-o para o
    dicionario, mas achei mais interessante, fácil, intuitivo e de maior
    otimização de operações e memória, se a skip list fosse implementada
    espeficicamente para o TAD dicionario. Logo, essa foi a decisão de
    implementação tomada.    */

typedef struct node
{
    char word[SIZE_OF_VERBETE], definition[SIZE_OF_DEFINITION];
    struct node *next, *down;
}   node_t;

typedef struct skiplist
{
    short int level, max_level;
    node_t *upleft;
}   dictionary_t;

// funcoes auxiliares no desenvolvimento do proprio TAD
void dictionary_create_level(dictionary_t *dic);
unsigned short int dictionary_generate_node_level();
node_t *dictionary_search_node(dictionary_t *dic, char *word);
void dictionary_print_node(node_t *p);

// ----- funcoes oferecidas ao usuario

// aloca memoria para um dicionario e retorna seu endereço ao usuario
dictionary_t *dictionary_create()
{
    dictionary_t *dic = (dictionary_t *) calloc(1, sizeof(dictionary_t));
    assert(dic != NULL);

    dic -> level = -1;
    dic -> max_level = -1;
    dic -> upleft = NULL;

    return dic;
}

// insere a palavra passada como argumento no dicionário passado como argumento
// (com a respectiva definicao). Retorna 1 em caso de sucesso, 0 caso contrário
// (palavra já inserida, por exemplo)
unsigned short int dictionary_insert(dictionary_t *dic, char *word, char *definition)
{
    assert(dic != NULL);

    // PARTE 1 do algoritmo de inserção em SKIPLIST - Criação e atualização
    // do vetor updates com os nós imediatamente anteriores ao local em que
    // iremos inserir um novo nó em cada lista da skiplist.

    // verifica se a palavra já está no dicionário com a função busca.
    // Se a palavra não estiver no dicionário, search_node NULL.
    if (dictionary_search_node(dic, word) != NULL)
    {
        return 0;
    }

    if (dic -> max_level == -1)
    {
        dictionary_create_level(dic);
    }

     // updates é o vetor que armazena os ponteiros anteriores ao local que precisamos
    // inserir um novo nó. Usa-se o valor de (dic -> max_level + 1) porque lidamos
    // com o level inicial == 0. Ou seja, a lista com max_level 1, possui 2 leveis,
    // e precisamos de 2 espaços no vetor updates para armazenar o anterior em cada
    // uma das duas listas.
    node_t **updates = (node_t **) calloc((dic -> max_level + 1), sizeof(node_t *));
    assert(updates != NULL);

    // variável que armazenará de quantos leveis o nó fará parte.
    unsigned short int node_level = dictionary_generate_node_level();

    // se o level do novo nó for maior que o level atual da lista, significa
    // que teremos de armazenar também os updates de leveis que ainda não existem,
    // que no caso, estarão apontando para o -1. Logo, serão necessários
    // node_level + 1 espaços no vetor.
    if (node_level > dic -> max_level)
    {
        // uso de calloc e free para alocar a memoria e inicializá-la com 0
        // de maneira mais prática.
        node_t **aux = calloc((node_level + 1), sizeof(node_t *));
        assert(aux != NULL);
        free(updates);
        updates = aux;
    }

    dic -> level = dic -> max_level;
    node_t *p = dic -> upleft;
    while (dic -> level > 0)
    {
        while (p -> next != NULL && strcmp(p -> next -> word, word) < 0)
        {
            p = p -> next;
        }
        updates[dic -> level] = p;
        // Sem risco de que p -> down seja NULL, visto que estamos no laço
        // de listas acima da local
        p = p -> down;
        (dic -> level)--;;
    }

    // Laço que iterage com a lista local
    // p pode estar apontando para nulo no caso do dicionario ainda estar vazio
    while (p != NULL && p -> next != NULL && strcmp(p -> next -> word, word) < 0)
    {
        p = p -> next;
    }
    updates[dic -> level] = p;

    // PARTE 2 - Inserção dos nós em níveis já existentes

    // A insercao de um novo nó nas listas se sucede de maneira crescente, ou seja,
    // do nó local até a última linha expressa, funcionando como inserções em listas
    // encadeadas comuns. Aqui também lidamos o caso do primeiro nó a ser inserido
    unsigned short int current_level = 0;

    while (current_level <= dic -> max_level && current_level <= node_level)
    {
        node_t *aux = (node_t *) calloc(1, sizeof(node_t));
        assert(aux != NULL);

        strcpy(aux -> word, word);
        strcpy(aux -> definition, definition);
        aux -> down = NULL;
        // desnecessario inicializar aux -> next com NULL, porque se ele for o ultimo
        // da lista, ao receber updates[current] -> next, já receberá NULL, caso não,
        // já estará apontando para o próximo nó da lista, com um único comando.
        aux -> next = updates[current_level] -> next;

        if (current_level > 0)
        {
            aux -> down = updates[current_level - 1] -> next;
        }

        updates[current_level] -> next = aux;
        current_level++;
    }

    // PARTE 3 - Criação de novos níveis, caso necessário
    for (int i = dic -> max_level + 1; i <= node_level; i++)
    {
        dictionary_create_level(dic);

        node_t *aux = (node_t *) calloc(1, sizeof(node_t));
        assert(aux != NULL);

        strcpy(aux -> word, word);
        strcpy(aux -> definition, definition);
        // acabamos de criar um novo level, logo, aux -> next sempre apontará
        // para nulo, o único nó no level é o "-1".
        aux -> next = dic -> upleft -> next;
        aux -> down = updates[i - 1] -> next;
        updates[i] = dic -> upleft;
        dic -> upleft -> next = aux;
    }

    free(updates);

    return 1;
}

// remove a palavra passada como argumento do dicionário passado como argumento.
// retorna 1 em caso de sucesso, 0 caso contrário (palavra não existente no dicionario)
unsigned short int dictionary_remove(dictionary_t *dic, char *word)
{
    assert(dic != NULL);

    node_t *p = dictionary_search_node(dic, word);
    if (p == NULL || dic -> max_level == -1)
    {
        return 0;
    }

    p = dic -> upleft;
    node_t **updates = (node_t **) calloc((dic -> max_level + 1), sizeof(node_t *));
    assert(updates != NULL);

    dic -> level = dic -> max_level;
    // setando os ponteiros do vetor updates para os anteriores nas linhas expressas
    while (dic -> level > 0)
    {
        while (p -> next != NULL && strcmp(p -> next -> word, word) < 0)
        {
            p = p -> next;
        }
        updates[dic -> level] = p;
        p = p -> down;
        (dic -> level)--;
    }

    // setando o update da linha local
    while (p -> next != NULL && strcmp(p -> next -> word, word) < 0)
    {
        p = p -> next;
    }
    updates[dic -> level] = p;

    // iniciando a remoção
    unsigned short int current_level = 0;
    node_t *aux = NULL;
    while (current_level <= dic -> max_level)
    {
        if (updates[current_level] -> next != NULL &&
            strcmp(updates[current_level] -> next -> word, word) == 0)
        {
            aux = updates[current_level] -> next;
            updates[current_level] -> next = aux -> next;
            free(aux);
        }
        current_level++;
    }

    // remove os últimos níveis da lista se o último for removido.
    // Exemplo: nivel 0: ~
    //          nivel 1: ~
    //          nivel 2: dado 25
    // se o 25 for removido, desalocamos a memória de todos os uplefts anteriores
    // e deixamos a skiplist vazia. Quando um nó é o único de um nível, assim que
    // o removermos, o upleft estará apontando para NULL. Também precisamos verificar
    // se dic -> upleft já está em NULL, porque há a possibilidade de que estejamos
    // removendo o único elemento da lista e nosso dicionário volte a estar vazio.
    while (dic -> upleft != NULL && dic -> upleft -> next == NULL)
    {
        aux = dic -> upleft;
        node_t *aux2 = aux -> down;
        (dic -> max_level)--;
        free(aux);
        dic -> upleft = aux2;
    }
    free(updates);

    return 1;
}

// altera a definicao da palavra word para a definicao passada para correction, no dicionario
// passado como argumento. Retorna 1 caso a operação seja bem sucedida, 0 caso não.
unsigned short int dictionary_change(dictionary_t *dic, char *word, char *correction)
{
    assert(dic != NULL);

    node_t *p = dictionary_search_node(dic, word);

    if (p == NULL)
        return 0;

    strcpy(p -> definition, correction);
    return 1;
}

// imprime a palavra passada como argumento e sua definicao. Retorna 1 caso a
// operacao seja bem sucedida e 0 caso contrario (palavra nao encontrada, por exemplo)
unsigned short int dictionary_print_word(dictionary_t *dic, char *word)
{
    assert(dic != NULL);

    // se houver a palavra na lista, p estará apontando para o nó na lista
    // local que o contém
    node_t *p = dictionary_search_node(dic, word);

    if (p != NULL)
    {
        dictionary_print_node(p);
        printf("\n");
        return 1;
    }

    return 0;
}

// imprime todas as palavras no dicionario dic que iniciem o caracter 'letter'
// retorna 1 caso a impressao seja bem sucedida e 0 caso nao haja nenhuma palavra
// com a letra inicial recebida
unsigned short int dictionary_print_letter(dictionary_t *dic, char letter)
{
    assert(dic != NULL);

    char letter_as_string[2];
    letter_as_string[0] = letter;
    letter_as_string[1] = '\0';

    if (dic -> max_level == -1)
    {
        return 0;
    }

    node_t *p = dic -> upleft;
    dic -> level = dic -> max_level;

    // iteração vertical
    while (dic -> level > 0)
    {
        // enquanto p -> word for menor que a letra, recebe prox
        while (p -> next != NULL && (strcmp(p -> next -> word, letter_as_string) < 0))
        {
            p = p -> next;
        }

        if (p -> down != NULL)
        {
            p = p -> down;
            (dic -> level)--;
        }
    }

    // aqui, estamos necessariamente no nível 0 (trilho local)
    while (p -> next != NULL && (strcmp(p -> next -> word, letter_as_string) < 0))
    {
        p = p -> next;
    }

    if (p -> next == NULL)
    {
        return 0;
    }
    // ao fim desses passos anteriores, p está apontando para a ultima palavra do dicionario
    // na linha local que se inicia com letra - 1 na tabela ASCII.

    // verificando se há alguma palavra no dicionário que se inicie com a letra
    // entre letra - 1 e letra + 1 na tabela ASCII
    char prox_letter[2];
    prox_letter[0] = letter + 1;
    prox_letter[1] = '\0';
    if (strcmp(p -> next -> word, prox_letter) > 0)
    {
        return 0;
    }

    p = p -> next;
    while (p != NULL && strcmp(p -> word, prox_letter) < 0)
    {
        dictionary_print_node(p);
        printf("\n");
        p = p -> next;
    }

    return 1;
}

// libera a funcao usada pelo dicionario
void dictionary_destroy(dictionary_t *dic)
{
    if (dic == NULL)
    {
        return;
    }

    if (dic -> max_level == -1)
    {
        free(dic);
        return;
    }

    dic -> level = dic -> max_level;
    while (dic -> level >= 0)
    {
        node_t *p = dic -> upleft;
        node_t *aux = dic -> upleft -> down;

        node_t *aux_ant = NULL;
        while (p -> next != NULL)
        {
            aux_ant = p;
            p = p -> next;
            free(aux_ant);
        }

        free(p);
        p = aux;
        dic -> upleft = aux;

        (dic -> level)--;
    }
    free(dic);
}


// --------- funcoes auxiliares no desenvolvimento do proprio TAD

unsigned short int dictionary_generate_node_level()
{
    unsigned short int node_level = 0;

    while (1)
    {
        // 32768 = valor maximo armazenável em um unsigned short int
        // na máquina que utilizo
        unsigned short int random = rand() % 32768;
        if (random % 2)
        {
            node_level++;
        }
        else
        {
            break;
        }
    }
    return node_level;
}

void dictionary_create_level(dictionary_t *dic)
{
    assert(dic != NULL);

    node_t *aux = dic -> upleft;
    node_t *p = (node_t *) calloc(1, sizeof(node_t));
    strcpy(p -> word, "-1");
    p -> next = NULL;
    p -> down = aux;

    (dic -> max_level)++;
    dic -> upleft = p;
}

// retorna o endereço do nó específico que contém a palavra word no dicionario dic
node_t *dictionary_search_node(dictionary_t *dic, char *word)
{
    assert(dic != NULL);

    if (dic -> max_level == -1)
    {
        return 0;
    }
    node_t *p = dic -> upleft;
    dic -> level = dic -> max_level;

    // iteração vertical
    while (dic -> level > 0)
    {
        // enquanto p -> word for menor que a palavra procurada, recebe prox
        while (p -> next != NULL && (strcmp(p -> next -> word, word) <= 0))
        {
            p = p -> next;
        }

        if (p -> down != NULL)
        {
            p = p -> down;
            (dic -> level)--;
        }
    }

    // aqui, estamos necessariamente no nível 0 (trilho local)
    while (p -> next != NULL && (strcmp(p -> next -> word, word) <= 0))
    {
        p = p -> next;
    }

    if (strcmp(p -> word, word) == 0)
    {
        return p;
    }
    return NULL;
}

// imprime o conteúdo de um único nó recebido como argumento, sem \n ao fim
void dictionary_print_node(node_t *p)
{
    if (p != NULL)
        printf("%s %s", p -> word, p -> definition);
}

