#define TamPilha 100

typedef struct pilha pilha_t;

pilha_t *create();
void destroy(pilha_t *p);
int isFull(pilha_t *p);
int isEmpty(pilha_t *p);
int push(pilha_t *p, void *x);
int pop(pilha_t *p, void **x);
int top(pilha_t *p, void **x);
