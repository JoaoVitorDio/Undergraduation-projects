typedef struct
{
    int *vetor, topo;
}pilha;

void cria_pilha(pilha *p1);
void pilha_pop(pilha *p1, int *x);
void pilha_push(pilha *p1, int x);
void pilha_empty(pilha *p1);
void pilha_destroy(pilha *p1);
unsigned char pilha_is_empty(pilha *p1);