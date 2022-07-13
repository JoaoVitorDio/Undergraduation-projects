typedef int elem;
typedef struct node node_t;

typedef struct treap
{
    node_t *root;
}   treap_t;

// Aloca memória e inicializa uma treap, retornando o seu endereço
treap_t *treap_create();

// retorna 1 caso a treap passada como argumento esteja vazia e 0 caso contrário.
int treap_is_empty(treap_t *a);

// libera a memória alocada pela árvore.
void treap_destroy(treap_t *a);

// imprime a arvore no formato: (pai(filhoesq, filhodir))
void treap_print(node_t *root);

// retorna a altura do nó passado como argumento
int treap_height(node_t *root);

// retorna 1 caso um nó com o valor do elemento seja encontrado e 0 caso contrário.
int treap_search(treap_t *treap, elem x);

// insere o numero passado como argumento, com a prioridade passada como argumento, na treap
int treap_insert(treap_t *a, elem x, int prio);

// remove o elemento x da treap.
int treap_remove(treap_t *a, elem x);

// imprime a árvore passada como argumento com o percurso pré-ordem.
void treap_preorder(treap_t *a);

// imprime a treap passada como argumento com o percurso em-ordem.
void treap_inorder(treap_t *a);

// imprime a treap passada como argumento com o percurso pos-ordem.
void treap_postorder(treap_t *a);

// imprime a treap passada como argumento em largura.
void treap_breadth_first(treap_t *treap);