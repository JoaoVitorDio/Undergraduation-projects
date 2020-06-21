#include <stdio.h>

int main () {

	int order, lin, col, countin, countfim, dif;

	while (1) {
		scanf ("%d", &order);
		
		if (order==0)
		break;
	
		int matriz[order][order];
	
		countin = 0;
		countfim = order;
		dif = order/2;
		
		/* estratégia: escrever matrizes que se sobreponham consecutivamente. A primeira matriz preenche todos os campos com 1, a segunda, preenche todos 
		os campos que não são borda	com 2, a próxima, todos que não são borda 2, com 3, e assim sucessivamente.*/
		
		while (1){
			
		    for (lin=countin;lin<countfim;lin++) {
		        for (col=countin;col<countfim;col++) {
		        	matriz[lin][col] = countin+1;		
		        }
		    }
		    
		    countin++;
		    countfim--;
		    
		    if (countin > dif)
		    break;   
		}
		
		// imprimindo a matriz resultante
	    for (lin=0;lin<order;lin++) {
	        for (col=0;col<order;col++) {
	        	if (col==0)
	            printf ("%3d", matriz[lin][col]);
	            else
	            printf (" %3d", matriz[lin][col]);
	
	        }
	    printf ("\n");
  		}   
  		
	printf ("\n");
    
	}
	return 0;
}

