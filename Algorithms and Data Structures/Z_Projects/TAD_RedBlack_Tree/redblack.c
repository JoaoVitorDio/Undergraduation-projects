#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "redblack.h"

#define RED 1
#define BLACK 0

// Propriedades da árvore rubro-negra:
// Arestas vermelhas sempre se ligam com o filho esquerdo
// A incidencia máxima de uma aresta vermelha em um nó é 1
// O caminho das folhas à raíz é sempre igual.

node_t *redblack_min_node(node_t *root);
node_t *redblack_max_node(node_t *root);

struct node
{
    node_t *left, *right;
    elem info;
    unsigned short int color;
};

redblack_t *redblack_create()
{
    redblack_t *a = (redblack_t *) calloc(1, sizeof(redblack_t));
    a -> root = NULL;
    return a;
}

int redblack_is_empty(redblack_t *a)
{
    assert(a != NULL);
    if (a -> root == NULL)
    {
        return 1;
    }
    return 0;
}

// desalocação recursiva e interna
void redblack_destroy_recurs(node_t *root)
{
    if (root != NULL)
    {
        redblack_destroy_recurs(root -> left);
        redblack_destroy_recurs(root -> right);
        free(root);
    }
}

// desalocação de memória usada pelo usuário
void redblack_destroy(redblack_t *a)
{
    redblack_destroy_recurs(a -> root);
    free(a);
}

// imprime a arvore no formato: (pai(filhoesq, filhodir))
void redblack_print(node_t *root)
{
    if (root != NULL)
    {
        printf("%d(", root -> info);
        redblack_print(root -> left);
        printf(",");
        redblack_print(root -> right);
        printf(")");
    }
    else
    {
        printf("null");
    }
}

int redblack_height(node_t *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int alt_left = 1 + redblack_height(root -> left);
    int alt_right = 1 + redblack_height(root -> right);

    if (alt_left > alt_right)
    {
        return alt_left;
    }
    else
    {
        return alt_right;
    }
}

// função busca interna e recursiva
node_t *redblack_search_recurs(node_t *root, elem x)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root -> info == x)
    {
        return root;
    }
    else if (x < root -> info)
    {
        return redblack_search_recurs(root -> left, x);
    }
    else
    {
        return redblack_search_recurs(root -> right, x);
    }
}

// função busca de conhecimento do usuário, retorna 1 caso haja
// o elemento passado como argumento e 0 caso não
int redblack_search(redblack_t *redblack, elem x)
{
    if (redblack_search_recurs(redblack -> root, x) != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// --------- Funções auxiliares utilizadas pelo TAD LLRB: ----------

// função específica do TAD usada para auxiliar na função remoção
// essa função específica não se aproveita da árvore ABB para percorrer
node_t *redblack_search_father(node_t *root, elem x)
{
    if (root == NULL)
        return NULL;
    if (root -> left != NULL && root -> left -> info == x)
        return root;
    if (root -> right != NULL && root -> right -> info == x)
        return root;

    // busca pelo pai/filho na esquerda
    node_t *p = redblack_search_father(root -> left, x);
    if (p == NULL) // se não encontrar, busca pela direita
        p = redblack_search_father(root -> right, x);

    return p;
}

// rotação simples para a esquerda, que já inverte as cores das arestas
node_t *rotate_ee(node_t *desb)
{
    node_t *aux = desb -> right;
    desb -> right = aux -> left;
    aux -> left = desb;
    aux -> color = desb -> color;
    desb -> color = RED;
    return aux;
}

// rotação simples para a direita, que já inverte as cores das arestas
node_t *rotate_dd(node_t *desb)
{
    node_t *aux = desb -> left;
    desb -> left = aux -> right;
    aux -> right = desb;
    aux -> color = desb -> color;
    desb -> color = RED;
    return aux;
}

// função que retorna a cor do nó
int redblack_which_color(node_t *p)
{
    if (p == NULL)
    {
        return BLACK;
    }
    return p -> color;
}

// inverte a cor do pai e de seus filhos. Não altera a estrutura ou conteúdo da árvore.
void redblack_change_color(node_t *p)
{
    p -> color = !(p -> color);
    if (p -> left != NULL)
    {
        p -> left -> color = !p -> left -> color;
    }
    if (p -> right != NULL)
    {
        p -> right -> color = !p -> right -> color;
    }
}

// -----------------------------------------------------------------

// Função insere, de funcionamento recursivo, interna do TAD
node_t *redblack_insert_recurs(node_t *root, elem x)
{
    // caso base da recursão: Encontrou o seu lugar ou insere na raíz
    if (root == NULL)
    {
        node_t *p = (node_t *) calloc(1, sizeof(node_t));
        p -> left = NULL;
        p -> right = NULL;
        p -> color = RED;
        p -> info = x;
        root = p;
        return root;
    }

    // encontrando o lugar em que devemos inserir o nó. Assim que chegar ao seu lugar,
    // será inserido e teremos de verificar nas chamadas acima se houve algum problema.
    // Porém, as LLRBs nos garantem que os problemas de desbalanceamento na inserção
    // são locais.
    if (x < root -> info)
    {
        root -> left = redblack_insert_recurs(root -> left, x);
    }
    else
    {
        // já procuramos se o elemento existe na função abstrata, então, se o código
        // estiver aqui, significa que o elemento é maior que root -> info.
        root -> right = redblack_insert_recurs(root -> right, x);
    }

    // verificações de ajuste na árvore
    // 1° caso: O filho da direita está com aresta vermelha e o filho da esquerda está com aresta preta.
    // Pelas regras da LLRB, apenas filhos esquerdos podem se ligar com arestas vemelhas, então, rotação EE.
    if (redblack_which_color(root -> right) == RED && redblack_which_color(root -> left) == BLACK)
    {
        root = rotate_ee(root);
    }
    // Segundo caso: Duas arestas vermelhas consecutivas.
    // Pela regra da LLRB, um nó contém ligação com no máximo, uma aresta vermelha.
    // Essa rotação deixará a próxima raíz com dois filhos com raíz vermelha, mas será ajustado na verificação
    // seguinte.
    if (redblack_which_color(root -> left) == RED && redblack_which_color(root -> left -> left) == RED)
    {
        root = rotate_dd(root);
    }
    // 3° caso: Dois filhos com aresta vermelha
    if (redblack_which_color(root -> left) == RED && redblack_which_color(root -> right))
    {
        redblack_change_color(root);
    }

    return root;
}

// Insere o numero x passado como argumento na redblack tree. Essa é a função
// abstrata utilizada pelo usuário, chama outra função interna recursiva internamente
// para resolver o problema.
int redblack_insert(redblack_t *a, elem x)
{
    assert(a != NULL);

    // garantindo que queremos inserir um elemento diferente e retornando erro
    if (redblack_search(a, x))
        return 0;

    a -> root = redblack_insert_recurs(a -> root, x);
    return 1;
}

// Função abstraída utilizada pelo usuário e que recebe a árvore toda como argumento
// recebe um elemento como argumento e retorna o seu sucessor na árvore (supondo uma
// impressao em ordem, seria o imediatamente a direita do elemento)
// o sucessor será retornado por referencia para que a função retorne erros também

// Tanto a função sucessor quando a função predecessor foram feitas com base no
// conteúdo encontrado em https://joaoarthurbm.github.io/eda/posts/bst/
int redblack_successor(redblack_t *redblack, elem x, int *successor)
{
    assert(redblack != NULL);
    node_t *aux = redblack_search_recurs(redblack -> root, x);
    if (aux == NULL) // elemento nao encontrado na arvore, retorna erro
        return 0;

    // para encontrar o sucessor de um número numa árvore, existem alguns casos:
    // 1° caso: Há sub-árvore da direita. O sucessor será o menor número dessa
    // sub-árvore
    if (aux -> right != NULL)
    {
        aux = redblack_min_node(aux -> right);
        *successor = aux -> info;
        return 1;
    }
    else
    {
        // 2° caso: Não há sub-árvore da direita. O sucessor será o seu menor ancestral
        // maior que o número. Essa operação, feita da maneira com que está aqui, possui
        // complexidade de log n * log n, porque usamos a função busca pai para encontrar
        // esses ancestrais. Outras soluções seriam utilizar a impressão em ordem (O(n))
        // e pegar o número a direita, ou, utilizar recursão com flags em que a cada
        // fim de recursão, verificamos se o pai é maior que o número, que seria o mais
        // efetivo, mas também, de implementação mais complicada.
        node_t *father = redblack_search_father(redblack -> root, aux -> info);
        while (father != NULL && father -> info < aux -> info)
        {
            father = redblack_search_father(redblack -> root, father -> info);
        }
        if (father == NULL)
            return 0;
        *successor = father -> info;
        return 1;
    }

    return 0;
}

// Recebe como argumento a árvore, o elemento que se está buscando o predecessor e o
// endereço da variável em que o seu predecessor será colocado. Retorna 1 caso sucesso
// e 0 caso contrário.

// Tanto a função sucessor quanto a função predecessor foram feitas com base no
// conteúdo encontrado em https://joaoarthurbm.github.io/eda/posts/bst/
int redblack_predecessor(redblack_t *redblack, elem x, int *predecessor)
{
    assert(redblack != NULL);

    node_t *aux = redblack_search_recurs(redblack -> root, x);
    if (aux == NULL) // elemento nao encontrado na arvore, retorna erro
        return 0;

    // para encontrar o predecessor de um número numa árvore, existem alguns casos:
    // 1° caso: Há sub-árvore à esquerda. O sucessor será o maior número dessa
    // sub-árvore
    if (aux -> left != NULL)
    {
        aux = redblack_max_node(aux -> left);
        *predecessor = aux -> info;
        return 1;
    }
    else
    {
        // 2° caso: Não há sub-árvore da esquerda. O sucessor será o seu maior ancestral
        // menor que o número. Essa operação, feita da maneira com que está aqui, possui
        // complexidade de log n * log n, porque usamos a função busca pai para encontrar
        // esses ancestrais. Outras soluções seriam utilizar a impressão em ordem (O(n))
        // e pegar o número a esquerda, ou, utilizar recursão com flags em que a cada
        // fim de recursão, verificamos se o pai é menor que o número, que seria o mais
        // efetivo, mas também, de implementação mais complicada.
        node_t *father = redblack_search_father(redblack -> root, aux -> info);
        while (father != NULL && (father -> info) > (aux -> info))
        {
            father = redblack_search_father(redblack -> root, father -> info);
        }
        if (father == NULL)
            return 0;
        *predecessor = father -> info;
        return 1;
    }

    return 0;
}

// função interna do TAD que procura pelo máximo a partir de determinado
// nó. Se usado recebendo a raíz da arvore como argumento, retorna o maior
// elemento da árvore. Pode ser usado para encontrar o sucessor de um número
// se for o filho -> dir e chamar a função para o pai -> esq
node_t *redblack_max_node(node_t *root)
{
    while (root -> right != NULL)
    {
        root = root -> right;
    }

    return root;
}

// Percorre a árvore em busca do maior elemento.
// retorna -1 caso erro (já que 0 pode ser um elemento da árvore)
int redblack_max(redblack_t *redblack)
{
    assert(redblack != NULL);

    node_t *aux = redblack_max_node(redblack -> root);
    if (aux == NULL)
    {
        return -1;
    }
    else
    {
        return aux -> info;
    }
}

// função interna do TAD que procura pelo mínimo a partir de determinado
// nó. Se usado recebendo a raíz da arvore como argumento, retorna o menor
// elemento da árvore. Pode ser usado para encontrar o predecessor de um número
// na árvore, assim como em operações de remoção em outros tipos de árvore.
node_t *redblack_min_node(node_t *root)
{
    while (root -> left != NULL)
    {
        root = root -> left;
    }

    return root;
}

// Percorre a árvore em busca do maior elemento.
// retorna -1 caso erro (já que 0 pode ser um elemento da árvore)
int redblack_min(redblack_t *redblack)
{
    assert(redblack != NULL);

    node_t *aux = redblack_min_node(redblack -> root);
    if (aux == NULL)
    {
        return -1;
    }
    else
    {
        return aux -> info;
    }
}

// função interna recursiva de impressão em pré-ordem
void redblack_preorder_recurs(node_t *root)
{
    if (root != NULL)
    {
        printf("%d ", root -> info);
        redblack_preorder_recurs(root -> left);
        redblack_preorder_recurs(root -> right);
    }
}

// função impressão pré-ordem oferecida ao usuário e abstraída, recebendo apenas
// a árvore como argumento.
void redblack_preorder(redblack_t *a)
{
    redblack_preorder_recurs(a -> root);
    printf("\n");
}

// função interna recursiva de impressão em-ordem
void redblack_inorder_recurs(node_t *root)
{
    if (root != NULL)
    {
        redblack_inorder_recurs(root -> left);
        printf("%d ", root -> info);
        redblack_inorder_recurs(root -> right);
    }
}

// função impressão em-ordem oferecida ao usuário e abstraída,
// recebendo apenas a árvore como argumento.
void redblack_inorder(redblack_t *a)
{
    redblack_inorder_recurs(a -> root);
    printf("\n");
}

// função interna recursiva de impressão em pós-ordem
void redblack_postorder_recurs(node_t *root)
{
    if (root != NULL)
    {
        redblack_postorder_recurs(root -> left);
        redblack_postorder_recurs(root -> right);
        printf("%d ", root -> info);
    }
}

// função impressão pós-ordem oferecida ao usuário e abstraída,
// recebendo apenas a árvore como argumento.
void redblack_postorder(redblack_t *a)
{
    redblack_postorder_recurs(a -> root);
    printf("\n");
}