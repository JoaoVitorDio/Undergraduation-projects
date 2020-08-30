#include <stdio.h>
#include <string.h>

int main() 
{
    FILE *arquivo;
    arquivo = fopen("arquivo.txt", "r+");
    if (arquivo == NULL)
    {
        printf("Falha ao abrir o arquivo para leitura.\n");
    }
    
    char matriz[10][100];
    
    int i = 0;
    
    while(!feof(arquivo)) 
    {
        fgets(matriz[i++], 100, arquivo);
    }
    
    for (int j = 0; j < i; j++)
    {
        printf("Linha %d: %s", j, matriz[j]);
    }
    
    fclose(arquivo);
    
    return 0;
}