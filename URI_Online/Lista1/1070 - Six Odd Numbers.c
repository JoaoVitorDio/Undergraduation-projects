#include <stdio.h>
#include <math.h>

int main () {
	
	int num, impar, auxiliar = 0;
	scanf ("%d", &num);
	
	if (num%2 == 1) {
	impar = num;
	}
	else {
		impar = num + 1;
	}
	
	while (auxiliar < 6) {
		
		printf ("%d\n", impar);
		auxiliar++;
		impar = impar + 2;
	}
	
	return 0;
}
