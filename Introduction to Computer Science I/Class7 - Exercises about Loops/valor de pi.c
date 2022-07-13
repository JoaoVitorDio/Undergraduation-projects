#include <stdio.h>
#include <conio.h>

/*	Calcular e escrever o valor do número p ,
	com n termos, usando a série p= 4 - 4/3 +
	4/5 - 4/7 + 4/9 - 4/11...	*/

int main () {

	int num;
	float dem = 1;
	double pi = 0;

	printf ("Digite a quantidade de termos na soma de pi");
	scanf ("%d", &num);

	dem = (dem*(-1));

	for (;num > 0;num--) {

		dem = (dem*(-1));
		pi = pi + (4/dem);

		if (dem<0)
			dem = dem - 2;
		else
			dem = dem +2;
	}

	printf ("O valor de pi na serie com n termos e: %lf", pi);

	getch();
	return 0;
}
