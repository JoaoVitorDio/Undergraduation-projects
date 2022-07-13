#include <stdio.h>
#include <math.h>

int main () {

	int number, array[10], count;

	scanf ("%d", &number);

	for (count=0;count<10;count++) {
		array[count] = number*(pow(2,count));
		printf ("N[%d] = %d\n", count, array[count]);
	}

	return 0;
}

