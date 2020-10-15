typedef int elem;
typedef struct lista lista_t;

lista_t *cria_lista();
void libera_lista(lista_t *l);
int insere_lista(lista_t *l, elem x);
int retira_lista(lista_t *l, elem x);
int tamanho_lista(lista_t *l);
int esta_na_lista(lista_t *l, elem x);
void imprime_lista(lista_t *l);
void inverte_lista(lista_t *l);