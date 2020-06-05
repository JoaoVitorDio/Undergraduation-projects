//	Prototipo: 
int* libera_memoria(int m, int n, int **matriz) 

//	Função que libera a memoria da matriz a partir dos parametros: 	Quantia de linhas, quantia de colunas e endereço da matriz.
int* libera_memoria(int m, int n, int **matriz) {
	
	int i;
	
	//	Verificando parametros
	if (matriz == NULL) 
		return NULL;
	
	if (m < 1 || n < 1) {
		printf ("Erro: Parametros invalidos.");
		return NULL;
	}
	
	for (i = 0; i < m; i++) {
		free (matriz[i]);
	}
	free (matriz);
	return NULL;
}
