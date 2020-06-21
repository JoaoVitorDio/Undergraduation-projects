#include <stdio.h>

int main () {

	int column, lin, col;
	float matriz[12][12], result = 0;
	char operation;

	scanf ("%d %c", &column, &operation);

	for (lin=0;lin<12;lin++) {
		for (col=0;col<12;col++) {
			scanf ("%f", &matriz[lin][col]);
		}
	}

	for (lin=0;lin<12;lin++) {
		result = result + matriz[lin][column];
	}

	if (operation == 'S')
		printf ("%.1f\n", result);

	if (operation == 'M') {
		result = result/12;
		printf ("%.1f\n", result);
	}

	return 0;
}

