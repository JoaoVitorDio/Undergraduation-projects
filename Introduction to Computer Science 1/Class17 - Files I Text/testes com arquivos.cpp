#include <stdio.h>

int main () {
	
	FILE *arquivo;
	int i, n;
	
	arquivo = fopen ("teste.txt", "a+");
	if (arquivo == NULL) {
	printf ("Erro ao abrir arquivo;");
	return 0;
	}
	
	fseek (arquivo, 0, SEEK_SET);
	
	for (i = 0; i < 5; i++) {
		fscanf (arquivo, "%d ", &n);
		printf ("%d\n", n);
	}
	
	fclose (arquivo);
	
	return 0;
}
