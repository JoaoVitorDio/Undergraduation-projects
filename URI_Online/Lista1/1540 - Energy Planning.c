#include <stdio.h>
#include <math.h>

int main() {

	int rounds, year1, year2, interval;
	unsigned long int media;
	double energy1, energy2, amount, media2;
	
	scanf ("%d", &rounds);
	
	for (;rounds > 0;rounds--) {
		
	    scanf ("%d %lf %d %lf", &year1, &energy1, &year2, &energy2);
	        if (year2 > year1) {
	        interval = year2 - year1;
	        amount = energy2 - energy1;
	        }
	        else {
	        interval = year1 - year2;
	        amount = energy1 - energy2;
	        }
	
	    media = amount/interval;
	    media2 = trunc(((amount/interval)-media)*100);
	    
	    if (media2>9)
	        printf ("%lu,%.lf\n", media, media2);
	        
	    else
	        printf ("%lu,%.lf0\n", media, media2);
	}
	return 0;
}

