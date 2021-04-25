#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "treap.h"
#include "fila.h"

struct node
{
    node_t *left, *right;
    elem info;
    int prio;
};

treap_t *treap_create()
{
    treap_t *a = (treap_t *) calloc(1, sizeof(treap_t));
    a -> root = NULL;
    return a;
}

int treap_is_empty(treap_t *a)
{
    assert(a != NULL);
    if (a -> root == NULL)
    {
        return 1;
    }
    return 0;
}

// desalocação recursiva e interna
void treap_destroy_recurs(node_t *root)
{
    if (root != NULL)
    {
        treap_destroy_recurs(root -> left);
        treap_destroy_recurs(root -> right);
        free(root);
    }
}

// desalocação de memória usada pelo usuário
void treap_destroy(treap_t *a)
{
    treap_destroy_recurs(a -> root);
    free(a);
}

// imprime a arvore no formato: (pai(filhoesq, filhodir))
void treap_print(node_t *root)
{
    if (root != NULL)
    {
        printf("%d(", root -> info);
        treap_print(root -> left);
        printf(",");
        treap_print(root -> right);
        printf(")");
    }
    else
    {
        printf("null");
    }
}

int treap_height(node_t *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int alt_left = 1 + treap_height(root -> left);
    int alt_right = 1 + treap_height(root -> right);

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
node_t *treap_search_recurs(node_t *root, elem x)
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
        return treap_search_recurs(root -> left, x);
    }
    else
    {
        return treap_search_recurs(root -> right, x);
    }
}

// função busca de conhecimento do usuário, retorna 1 caso haja
// o elemento passado como argumento e 0 caso não
int treap_search(treap_t *treap, elem x)
{
    if (treap_search_recurs(treap -> root, x) != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// função específica do TAD usada para auxiliar na função remoção
// essa função específica não se aproveita da árvore ABB para percorrer
node_t *treap_search_father(node_t *root, elem x)
{
    if (root == NULL)
        return NULL;
    if (root -> left != NULL && root -> left -> info == x)
        return root;
    if (root -> right != NULL && root -> right -> info == x)
        return root;

    // busca pelo pai/filho na esquerda
    node_t *p = treap_search_father(root -> left, x);
    if (p == NULL) // se não encontrar, busca pela direita
        p = treap_search_father(root -> right, x);

    return p;
}

// rotação simples para a esquerda
node_t *rotate_ee(node_t *desb)
{
    node_t *aux = desb -> right;
    desb -> right = aux -> left;
    aux -> left = desb;
    return aux;
}

// rotação simples para a direita
node_t *rotate_dd(node_t *desb)
{
    node_t *aux = desb -> left;
    desb -> left = aux -> right;
    aux -> right = desb;
    return aux;
}

// Recebe um nó como argumento e verifica se é uma folha
int treap_is_leaf(node_t *p)
{
    if (p -> left == NULL && p -> right == NULL)
        return 1;
    return 0;
}

// Recebe um nó como argumento e verifica se é uma semi-folha (apenas 1 filho)
// retorna 1 caso haja filho esquerdo e 2 caso haja filho direito.
int treap_is_semileaf(node_t *p)
{
    if (p -> left != NULL && p -> right == NULL)
        return 1;
    if (p -> left == NULL && p -> right != NULL)
        return 2;
    return 0;
}

node_t *treap_insert_recurs(node_t *root, elem x, int prio)
{
    if (root == NULL)
    {
        // alocação do nó folha
        root = (node_t *) calloc(1, sizeof(node_t));
        root -> info = x;
        root -> prio = prio;
        root -> left = NULL;
        root -> right = NULL;
        return root;
    }

    // encontrando e inserindo uma folha no lugar certo, como em qualquer ABB
    if (x < root -> info)
    {
        root -> left = treap_insert_recurs(root -> left, x, prio);

        // fazendo a rotação caso a prioridade do filho seja maior que a do pai (max_heap)
        // por usar recursão, acabamos por verificar toda a linhagem ao inserir um elemento.
        if (root -> left -> prio > root -> prio)
        {
            root = rotate_dd(root);
        }
    }
    else // Visto que não permitimos valores iguais na treap, se não é menor, é maior.
    {
        root -> right = treap_insert_recurs(root -> right, x, prio);

        // fazendo a rotação caso a prioridade do filho seja maior que a do pai (max_heap)
        // por usar recursão, acabamos por verificar toda a linhagem ao inserir um elemento.
        if (root -> right -> prio > root -> prio)
        {
            root = rotate_ee(root);
        }
    }

    return root;
}

int treap_insert(treap_t *a, elem x, int prio)
{
    assert(a != NULL);

    // garantindo que queremos inserir um elemento diferente e retornando erro
    if (treap_search(a, x))
        return 0;

    a -> root = treap_insert_recurs(a -> root, x, prio);
    return 1;
}

node_t *treap_remove_recurs(node_t *root, elem x)
{
    // não precisamos tratar o caso de não encontrar o elemento na arvore
    // porque já realizamos essa verificação em treap_remove
    if (x < root -> info)
    {
        root -> left = treap_remove_recurs(root -> left, x);
    }
    else if (x > root -> info)
    {
        root -> right = treap_remove_recurs(root -> right, x);
    }
    else // se estamos no nó a ser removido
    {
        // caso 1: Nó é uma folha => libera e seta o ponteiro do pai para null
        if (treap_is_leaf(root))
        {
            free(root);
            return NULL;
        }

        // caso 2: é uma semi-folha; Libera e seta ponteiro do pai para o unico filho
        int is_semileaf = treap_is_semileaf(root);
        if (is_semileaf)
        {
            node_t *aux = root;
            if (is_semileaf == 1)
            {
                root = root -> left;
            }
            else // is_semileaf contém 1 ou 2, 1 se há filho esq, 2 se filho dir
            {
                root = root -> right;
            }
            free(aux);
            return root;
        }

        // caso 3: Um nó interno com dois filhos, fazemos rotação EE até virar folha/semi-folha
        root = rotate_ee(root);
        root -> left = treap_remove_recurs(root -> left, x);
    }

    return root;
}


int treap_remove(treap_t *a, elem x)
{
    assert(a != NULL);

    // garantindo que queremos remover um elemento existente na treap
    if (!treap_search(a, x))
        return 0;

    a -> root = treap_remove_recurs(a -> root, x);
    return 1;
}

void treap_preorder_recurs(node_t *root)
{
    if (root != NULL)
    {
        printf("(%d, %d) ", root -> info, root -> prio);
        treap_preorder_recurs(root -> left);
        treap_preorder_recurs(root -> right);
    }
}

void treap_preorder(treap_t *a)
{
    treap_preorder_recurs(a -> root);
    printf("\n");
}

void treap_inorder_recurs(node_t *root)
{
    if (root != NULL)
    {
        treap_inorder_recurs(root -> left);
        printf("(%d, %d) ", root -> info, root -> prio);
        treap_inorder_recurs(root -> right);
    }
}

void treap_inorder(treap_t *a)
{
    treap_inorder_recurs(a -> root);
    printf("\n");
}

void treap_postorder_recurs(node_t *root)
{
    if (root != NULL)
    {
        treap_postorder_recurs(root -> left);
        treap_postorder_recurs(root -> right);
        printf("(%d, %d) ", root -> info, root -> prio);
    }
}

void treap_postorder(treap_t *a)
{
    treap_postorder_recurs(a -> root);
    printf("\n");
}

// breadth_first = impressão em largura
void treap_breadth_first(treap_t *treap)
{
    fila_t *fila = cria_fila();

    insere_fila(fila, treap -> root -> info);

    while(tamanho_fila(fila))
    {
        int aux = 0;
        remove_fila(fila, &aux);
        node_t *node_aux = treap_search_recurs(treap -> root, aux);
        printf("(%d, %d) ", node_aux -> info, node_aux -> prio);
        if (node_aux -> left != NULL)
        {
            insere_fila(fila, node_aux -> left -> info);
        }
        if (node_aux -> right != NULL)
        {
            insere_fila(fila, node_aux -> right -> info);
        }
    }
    printf("\n");

    libera_fila(fila);
}