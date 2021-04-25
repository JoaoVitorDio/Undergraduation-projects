typedef int elem;
typedef struct node node_t;

typedef struct redblack
{
    node_t *root;
}   redblack_t;

// Aloca memória e inicializa uma redblack, retornando o seu endereço
redblack_t *redblack_create();

// retorna 1 caso a redblack passada como argumento esteja vazia e 0 caso contrário.
int redblack_is_empty(redblack_t *a);

// libera a memória alocada pela árvore.
void redblack_destroy(redblack_t *a);

// imprime a arvore no formato: (pai(filhoesq, filhodir))
void redblack_print(node_t *root);

// retorna a altura do nó passado como argumento
int redblack_height(node_t *root);

// retorna 1 caso um nó com o valor do elemento seja encontrado e 0 caso contrário.
int redblack_search(redblack_t *redblack, elem x);

// Insere o numero x passado como argumento na redblack tree
int redblack_insert(redblack_t *a, elem x);

// Recebe como argumento a árvore, o elemento que se está buscando o sucessor e o
// endereço da variável em que o seu sucessor será colocado. Retorna 1 caso sucesso
// e 0 caso contrário.
int redblack_successor(redblack_t *redblack, elem x, int *successor);

// Recebe como argumento a árvore, o elemento que se está buscando o predecessor e o
// endereço da variável em que o seu predecessor será colocado. Retorna 1 caso sucesso
// e 0 caso contrário.
int redblack_predecessor(redblack_t *redblack, elem x, int *predecessor);

// Percorre a árvore em busca do maior elemento e o retorna ao usuário.
int redblack_max(redblack_t *redblack);

// Percorre a árvore em busca do menor elemento e o retorna ao usuário.
// retorna -1 caso erro (já que 0 pode ser um elemento da árvore)
int redblack_min(redblack_t *redblack);

// imprime a árvore passada como argumento com o percurso pré-ordem.
// retorna -1 caso erro (já que 0 pode ser um elemento da árvore)
void redblack_preorder(redblack_t *a);

// imprime a redblack passada como argumento com o percurso em-ordem.
void redblack_inorder(redblack_t *a);

// imprime a redblack passada como argumento com o percurso pos-ordem.
void redblack_postorder(redblack_t *a);