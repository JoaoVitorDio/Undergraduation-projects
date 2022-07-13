#include <stdio.h>
#include <stdlib.h>

/*	Faça um programa que calcule a media de nota dos alunos, alocando dinamicamente o vetor para armazenar esses dados	*/

int main () {
	
	int numalunos, i;
	float media, *v, soma = 0;
	
	printf ("Digite a quantidade de alunos:\n");
	scanf ("%d", &numalunos);
	
	if (numalunos < 1)
	return 0;
	
	v = (float *) calloc (numalunos, sizeof(float));
		if (v == NULL) 
		return 0;
	
	for (i = 0; i < numalunos; i++) {
		printf ("\nDigite a nota do %d aluno: ", i+1);
		scanf ("%f", &v[i]);
		soma += v[i];
	}
	
	media = soma/numalunos;
	
	free (v);

	printf ("\nA media da sala e: %.2f", media);

	return 0;
}
