#include <stdio.h>
#include <stdlib.h>
#include "merge.h"
#include <assert.h>

int main()
{
    //  Scaneando quantos vetores serão recebidos como entrada
    int quantia_vetores;
    scanf("%d", &quantia_vetores);

    /*  Criando um vetor para armazenar os tamanhos dos 'quantia_vetores' vetores.
        (Precisaremos desses valores ao fim do programa, não apenas na alocação de
        memória para os vetores) */
    int *tamanho_dos_vetores = (int *) calloc(quantia_vetores, sizeof(int));
    assert(tamanho_dos_vetores != NULL);

    for (int i = 0; i < quantia_vetores; i++)
    {
        scanf("%d", &tamanho_dos_vetores[i]);
    }

    /*  Criando um ponteiro de ponteiros ("matriz") para armazenar 'quantia_vetores',
        cada um de respectivo 'tamanho_dos_vetores[i]' tamanho. */
    int **vetores = (int **) calloc(quantia_vetores, sizeof(int *));
    assert(vetores != NULL);
    for (int i = 0; i < quantia_vetores; i++)
    {
        vetores[i] = (int *) calloc(tamanho_dos_vetores[i], sizeof(int));
    }

    /*  Preenchendo a matriz:   */
    for (int i = 0; i < quantia_vetores; i++)
    {
        for (int k = 0; k < tamanho_dos_vetores[i]; k++)
        {
            scanf("%d", &vetores[i][k]);
        }
    }

    /*  Verificando se li os vetores direito:   */
    for (int i = 0; i < quantia_vetores; i++)
    {
        printf("Vetor %d:\t", i);
        for (int k = 0; k < tamanho_dos_vetores[i]; k++)
        {
            printf("%d ", vetores[i][k]);
        }
        printf("\n");
    }
    
    /*  Fazendo um backup da matriz com os valores, visto que teremos de ordenar 
        os vetores recebidos com dois métodos diferentes. Se usássemos um único
        endereço de memória, o primeiro método que passasse já o organizaria e
        o segundo não registraria nenhuma comparação. Logo, precisamos de dois
        vetores de cada a serem ordenados.  
        Breve definição para o resto do código: O merge ordenará os vetores em
        **vetores e o insertion ordenará os vetores em **vetores2   */
        
    int **vetores2 = (int **) calloc(quantia_vetores, sizeof(int *));
    for (int i = 0; i < quantia_vetores; i++)
    {
        vetores2[i] = (int *) calloc(tamanho_dos_vetores[i], sizeof(int));
    }
    
    for (int i = 0; i < quantia_vetores; i++)
    {
        for (int k = 0; k < tamanho_dos_vetores[i]; k++)
        {
            vetores2[i][k] = vetores[i][k];
        }
    }
    
    for (int i = 0; i < quantia_vetores; i++)
    {
        /*  Criando e inicializando variáveis para armazenar os dados 
            de funcionamento dos algoritmos de ordenação insertion (gracioso...)  */
        /*  int trocasInsertion = 0, cmpInsertion = 0;
        insertion();
        printf("I %d %d %d\n", tamanho_dos_vetores[i], trocasInsertion, cmpInsertion); */
        
        /*  Criando e inicializando variáveis para armazenar os dados 
            de funcionamento dos algoritmos de ordenação merge (lindo)  */
        int trocasMerge = 0, cmpMerge = 0;
        merge(vetores[i], tamanho_dos_vetores[i], &trocasMerge, &cmpMerge);
        printf("M %d %d %d\n", tamanho_dos_vetores[i], trocasMerge, cmpMerge);
    }
    
    /*  Verificando se os vetores foram ordenados corretamente:   */
    for (int i = 0; i < quantia_vetores; i++)
    {
        printf("Vetor %d:\t", i);
        for (int k = 0; k < tamanho_dos_vetores[i]; k++)
        {
            printf("%d ", vetores[i][k]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < quantia_vetores; i++)
    {
        printf("Vetor2 %d:\t", i);
        for (int k = 0; k < tamanho_dos_vetores[i]; k++)
        {
            printf("%d ", vetores2[i][k]);
        }
        printf("\n");
    }

    /*  Liberando toda a memória alocada durante o programa:    */
    for (int i = 0; i < quantia_vetores; i++)
    {
        free(vetores[i]);
    }
    free(vetores);
    
    for (int i = 0; i < quantia_vetores; i++)
    {
        free(vetores2[i]);
    }
    free(vetores2);
   
    free(tamanho_dos_vetores);

    return 0;
}