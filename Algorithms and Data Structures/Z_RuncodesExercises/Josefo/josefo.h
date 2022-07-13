typedef int elem;
typedef struct lista lista_t;

lista_t *cria_lista();
//  Retorna um ponteiro para uma lista circular
void libera_lista(lista_t *l);
//  Libera a memória usada pela lista
int insere_lista(lista_t *l, elem x);
//  Insere um elemento no fim da lista (adjacente e anterior
//  ao sentinela da lista circular)
int retira_lista(lista_t *l, elem x);
//  retira um elemento da lista circular
int tamanho_lista(lista_t *l);
//  retorna o tamanho da lista
int esta_na_lista(lista_t *l, elem x);
//  retorna 1 caso o elemento passado como argumento esteja
//  na lista e 0 caso contrário
void imprime_lista(lista_t *l);
//  imprime a lista com espaços simples entre os valores e um \n ao fim
int josefo(lista_t *l, int soldado1, int random);
//  recebe uma lista circular com quaisquer valores, desde que não repetidos,
//  ordenados ou não, o soldado em que a contagem se inicia e uma constante 
//  (o intervalo) a ser contado para que um soldado seja morto, e retorna o 
//  numero do soldado sobrevivente.