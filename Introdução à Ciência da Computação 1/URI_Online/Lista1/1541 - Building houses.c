#include <stdio.h>
#include <math.h>

int main () {
	
	int met1, met2, percent, totalarea, land;
	
	while (1) {
		scanf ("%d", &met1);
		if (met1 == 0) {
			break;		
		}
		else {			
		scanf ("%d %d", &met2, &percent);
		totalarea = (met1*met2);
		totalarea = (totalarea*100)/percent;
		land = trunc(sqrt(totalarea));
		printf ("%d\n", land);	
		}		
	}
	
	return 0;
}
