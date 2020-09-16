#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  Recebe como argumento o vetor a ser ordenado e o seu tamanho.
void merge(int *vetor, int tamanho, int *trocasMerge, int *cmpMerge);

void intercala(int *vetor, int tamanho1, int tamanho2, int *trocasMerge, int *cmpMerge);