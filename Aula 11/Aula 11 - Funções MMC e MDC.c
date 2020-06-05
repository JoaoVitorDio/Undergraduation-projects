#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

	/* Crie duas funções que recebam 3 números inteiros. Uma delas deve retornar o máximo divisor comum (m.d.c.) e a outra, o mínimo múltiplo comum (m.m.c.)
	desses números. Crie um programa que leia 3 números inteiros, execute as duas funções e mostre o mmc e o mdc desses números. */

	int mmc(int x, int y, int z);
	int mdc(int x, int y, int z);


	void main {

	int x, y, z;
	int mmc, mdc;

	printf ("Digite 3 numeros no formato x y z\n");
	scanf ("%d %d %d", &x, &y, &z);

	// lembrando que talvez seja necessário mudar o nome da variável que vai invocar a função. Da outra vez, deu ruim rsrs bom conferir se é uma regra.

	mmc = mmc(x, y, z);
	printf ("o mmc de  %d, %d e %d e: %d\n", x, y, z, mmc);

	mdc = mdc(x, y, z);
	printf ("o mdc de  %d, %d e %d e: %d\n", x, y, z, mdc);


	getch();


}

	int mmc(int x, int y, int z) {
		int result;

		/* Crivo de erástotenes ou função para colocar primos em um array + if que vai andando no array (pegando o próximo primo); + divisão sucessiva pelo
		menor primo possível */

		return result;
	}
	int mdc(int x, int y, int z) {
		int result;

		// algoritmo de euclides

		return result;
	}
