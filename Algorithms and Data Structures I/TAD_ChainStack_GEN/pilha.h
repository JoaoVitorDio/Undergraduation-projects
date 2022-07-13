typedef int elem;
typedef struct pilha pilha_t;

pilha_t *cria_pilha();
//  Retorna o endereço de uma variável do tipo pilha_t
void libera_pilha(pilha_t *l);
//  Libera a memória alocada para o uso da pilha
int push_pilha(pilha_t *l, elem x);
//  Insere um elemento no topo da pilha
int pop_pilha(pilha_t *l, elem *x);
//  Retira o elemento do topo da pilha e o coloca na variável 
//  passada como argumento.
int retira_pilha(pilha_t *l, elem x);
//  Retira determinado elemento da pilha (independente de quantos
//  estejam nela)
int tamanho_pilha(pilha_t *l);
//  retorna um inteiro, o tamanho de elementos na pilha
int esta_na_pilha(pilha_t *l, elem x);
//  Retorna sim caso o elemento passado como argumento estiver na pilha
//  e não caso contrário
void imprime_pilha(pilha_t *l);
//  Imprime a pilha do topo à base
void inverte_pilha(pilha_t *l);
//  Inverte a pilha. Os últimos passam a ser os primeiros e vice-versa.

