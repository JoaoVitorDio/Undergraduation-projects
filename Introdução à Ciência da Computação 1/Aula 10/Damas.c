#include <stdio.h>
#include <conio.h>

/*		Uma matriz D8x8 pode representar a posição atual de um
		jogo de damas, sendo que 0 indica uma casa vazia, 2
		indica uma casa ocupada por uma peça branca e 1 indica
		uma casa ocupada por uma peça preta. Supondo que as
		peças pretas estão se movendo no sentido crescente das
		linhas da matriz D, determinar as posições das peças
		pretas que:
		(a) podem tomar peças brancas;
		(b) podem mover-se sem tomar peças;
		(c) não podem se mover.
		Obs: preencher o tabuleiro na declaração da matriz	*/

int main () {

	int matriz[8][8] = {{0,1,0,1,0,1,0,1}, {1,0,0,0,1,0,1,0}, {0,1,0,1,0,2,0,0}, {0,0,2,0,2,0,2,0},
						{0,1,0,2,0,1,0,1}, {0,0,0,0,2,0,0,0}, {0,2,0,0,0,2,0,0}, {2,0,2,0,2,0,2,0}};
	int lin, col, esquerda, direita, baixo, futesquerda, futdireita, futbaixo;

	/* Anotações sobre o jogo de damas: As peças apenas andam em linhas e colunas de paridades diferentes. Nunca haverá uma peça na posição [1][1] ou [3][1].
	Esse já é um bom ponto de partida para preencher o jogo. */

	/* Imprimindo a matriz para visualização de como está o jogo: */

	for (lin=0;lin<8;lin++) {
		printf ("\n%d  ", lin);
		for (col=0;col<8;col++) {
			printf (" %d", matriz[lin][col]);
		}
	}
	printf("\n\n    ");
	for(lin=0; lin<8; lin++) {
        printf("%d ", lin);
    }
    printf("\n\n");

    for (lin=0;lin<8;lin++) {
    	for (col=0;col<8;col++) {

    		// entrando na análise das possibilidades de uma peça preta. Não faz sentido analisarmos uma peça branca ou uma casa vazia.
	    	if (matriz[lin][col]==1) {

	    	esquerda 	=	col - 1;
	    	direita 	= 	col + 1;
	    	baixo 		= 	lin + 1;

	    	futesquerda =	col - 2;
	    	futdireita 	= 	col + 2;
	    	futbaixo 	= 	lin + 2;

	    	// Já eliminando a análise da linha 7, porque forma rainhas:

	    		if (lin==7)
	    			printf ("A peca [%d][%d] se tornou rainha e seus movimentos estao fora da previsao desse algoritmo", lin, col);

	    		else {

				// fazendo a análise das bordas:

					if (esquerda<0 || direita >7) {

	    			// borda esquerda:

	    			if (esquerda<0) {
	    				if (matriz[baixo][direita]==0)
		    				printf ("A peca na posicao [%d][%d] pode se mover.\n", lin, col);
		    			if (matriz[baixo][direita]==1)
		    				printf ("A peca na posicao [%d][%d] nao pode se mover.\n", lin, col);

		    			// não precisamos nos preocupar com o caso de uma peca branca seguida da parede, devido a paridade das casas que citamos acima.
						if (matriz[baixo][direita]==2) {
							if (matriz[futbaixo][futdireita]==0)
							printf ("A peca na posicao [%d][%d] pode comer uma peca branca.\n", lin, col);
							else
							printf ("A peca na posicao [%d][%d] nao pode se mover.\n");
						}
	    			}

	    			// borda direita:
	    			if (direita>7) {

	    				if (matriz[baixo][esquerda]==0)
		    				printf ("A peca na posicao [%d][%d] pode se mover.\n", lin, col);
	    				if (matriz[baixo][esquerda]==1)
		    				printf ("A peca na posicao [%d][%d] nao pode se mover.\n", lin, col);

						// aqui, precisamos nos preocupar com o caso [6][7]
						if (matriz[baixo][esquerda]==2) {
							if (futbaixo>7)
		    					printf ("A peca na posicao [%d][%d] nao pode se mover.\n", lin, col);
		    				// aqui, ja resolvemos esse caso e podemos nos preocupar apenas com os outros devido ao else ;)

		    				else {
		    					if (matriz[futbaixo][futdireita]==0)
		    					printf ("A peca na posicao [%d][%d] pode se mover.\n", lin, col);

		    					else
		    					printf ("A peca na posicao [%d][%d] nao pode se mover.\n", lin, col);

		    				}
						}
	    			}
	    		}

				// analise das peças no centro:

					else {

					// Eliminando o primeiro caso de peça bloqueada: esquerda e direita com peças pretas
						if (matriz[baixo][esquerda]==1 && matriz[baixo][direita]==1)
							printf ("A peca na posicao [%d][%d] nao pode se mover.\n", lin, col);


						else {

						// Caso alguma captura esteja disponível, ela é obrigatória, então...
							if (  ((matriz[baixo][esquerda]==2)&& (matriz[futbaixo][futesquerda]==0)) || ((matriz[baixo][direita]==2) && (matriz[futbaixo][futdireita]==0))  )
								printf ("A peca na posicao [%d][%d] pode comer uma peca branca.\n", lin, col);

						// Se ela não pode comer, ela está livre ou bloqueada.
							else {

								if ((matriz[baixo][esquerda]==0) || (matriz[baixo][direita]==0))
									printf ("A peca na posicao [%d][%d] pode se mover.\n", lin, col);
								else
									printf ("A peca na posicao [%d][%d] nao pode se mover.\n", lin, col);

							}
						}
					}
				}
	    	}
	    }
	}

	getch();
	return 0;
}
