// 	Prototipo:
int** somar_matriz(int m, int n, int** matriza, int** matrizb);

//	Função que calcula a soma de duas matrizes de dimensão igual (regra para a operação)
int** somar_matriz(int m, int n, int** matriza, int** matrizb) {
	int i, j, **v;
	
	v = alocar_matriz (m, n);
	
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			v[i][j] = matriza[i][j] + matrizb[i][j];
		}
	}
	return v;
}
