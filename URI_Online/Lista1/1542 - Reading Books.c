#include <stdio.h>

int main () {

	float Q, D, P, dias, totalpages, auxiliar;
	
	while (1) {
		scanf ("%f", &Q);
		if (Q == 0) {
			
			break;	
			
		}
		else {
					    
            scanf ("%f %f", &D, &P);
            
		    auxiliar = 1-(Q/P);
		    dias = D*(1/(auxiliar));
		    totalpages = trunc(dias*Q);
		    
   			if (totalpages == 1)
                printf ("%.f pagina\n", totalpages);				
			else 
                printf ("%.f paginas\n", totalpages);
    	}
	}
    
	return 0;	
}

