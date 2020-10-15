//  Para o uso adequado, basta definir o tamanho da constante
//  TamFila às respectivas necessidades e manipular os ponteiros
//  de acordo com os protótipos das funções abaixo.
//  Como o padrão, sucesso na operação retorna 1. Ou seja,
//  a função "isEmpty" retorna 1 se estiver vazia e 0 caso não.
#define TamFila 10

//  Utilize uma variável do tipo fila_t para manipular as funções.
typedef struct fila fila_t;

//  Inicialize uma fila a partir dessa função. Exemplo:
//  fila_t *ponteiro = criar();
fila_t *criar();

//  Retorna 1 caso fila vazia e 0 caso contrário.
int isEmpty(fila_t *f);

//  Retorna 1 caso fila cheia e 0 caso contrário.
int isFull(fila_t *f);

//  Insere qualquer tipo de elemento na fila.
int inserir(fila_t *f, void *x);

//  Remove o endereço de um item da fila e o armazena no endereço
//  passado como argumento.
int remover(fila_t *f, void **x);

//  Libera a memória alocada e destrói a fila criada.
void destruir(fila_t *f);
