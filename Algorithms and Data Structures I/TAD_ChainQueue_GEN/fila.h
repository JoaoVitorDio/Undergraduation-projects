typedef int elem;
typedef struct fila fila_t;

fila_t *cria_fila();
//  Retorna o endereço de uma variável do tipo fila_t
void libera_fila(fila_t *l);
//  Libera a memória alocada para o uso da fila
int insere_fila(fila_t *l, elem x);
//  Insere um elemento no fim da fila
int remove_fila(fila_t *l, elem *x);
//  Coloca o valor do primeiro elemento da fila na variável
//  x e desloca o início da fila para frente. (Fila anda)
int retira_fila(fila_t *l, elem x);
//  Retira determinado elemento da fila (independente de quantos
//  estejam nela)
int tamanho_fila(fila_t *l);
//  retorna um inteiro, o tamanho de elementos na fila.
int esta_na_fila(fila_t *l, elem x);
//  Retorna sim caso o elemento passado como argumento estiver na fila
//  e não caso contrário.
void imprime_fila(fila_t *l);
//  Imprime a fila do início ao fim.
void inverte_fila(fila_t *l);
//  Inverte a fila. Os últimos passam a ser os primeiros e vice-versa.