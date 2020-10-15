#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  Recebe como argumento o vetor a ser ordenado e o seu tamanho.
void merge(int *vetor, int tamanho);

/*  Recebe como argumento um vetor em que duas partes já estejam ordenadas
    e são sequenciais. Recebe o tamanho da primeira parte e o tamanho
    da segunda parte.   Devolve o vetor inteiramente ordenado.  */
void intercala(int *vetor, int tamanho1, int tamanho2);