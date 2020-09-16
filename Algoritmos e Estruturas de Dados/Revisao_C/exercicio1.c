#include <stdio.h>
#include <string.h>

/*  Leia um arquivo texto, a cada final de linha, adicione a linha
    lida em uma estrutura de ponteiros para ponteiros   */

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
    printf("\n");

    fclose(arquivo);

    return 0;
}