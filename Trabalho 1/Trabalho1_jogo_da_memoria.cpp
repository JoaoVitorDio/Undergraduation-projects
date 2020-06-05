#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*	O programa é um jogo da memória. Números são exibidos na tela e após 5 segundos são apagados; O usuário deve digitá-los na ordem em que apareceram.	*/

int main() {
    int count, array[20], streak = 1, digitado[20];

    /*Inicializa a sequencia de números aleatórios. Deve ser executada uma única vez no início do programa. */
    srand(time(NULL));
    // Armazenando a sequência de numeros aleatórios em um array para que possamos compará-la com a sequencia digitada pelo usuario.
    for (count = 0; count < 20 ; count++) {
    	array[count] = rand()%10;
    }

	// Apresentação do programa ao usuário.
	printf ("Bem vindo ao jogo da memoria!\n\nNa tela, serao apresentados numeros aleatorios. \nVoce tera 5 segundos para memoriza-los.\n");
	printf ("A tela sera apagada e o seu objetivo e digitar \nos numeros que apareceram na tela, na exata \nsequencia em que estavam.\n\n");
	printf ("Digite os numeros sem espacos. A cada rodada vencida,\na quantia de numeros apresentada aumentara.\n\n");
	
	printf("Para sair do jogo, basta digitar uma sequencia de teclas aleatorias. \n\nBoa sorte!\n\n");
	printf ("Digite qualquer tecla para iniciar\n\n");

	getch();
	
	system("cls");
    printf("Inicio do jogo!");
    Sleep(2000);
    system("cls");
	
	while(1) {
		
		printf ("A sequencia para memorizar e: ");
		for (count = 0; count < streak; count++) {
			 printf ("%d ", array[count]);	
		}
		
		/*Pausa a execução do programa. Argumento em milisegundos.*/
	    Sleep(5000);
	
	    /*Apaga a tela.*/
	    system("cls");
	    printf(" Tela apagada");
	    Sleep(2000);
	    system("cls");
	    
	    printf ("Digite a sequencia: ");
	    
	    /* Lendo os números digitados pelo usuário */
	    
	    for (count = 0; count < streak; count++) { 	
	    	/* Lidando com o scan... Mas usaremos o getch para que o usuario nao tenha que digitar enter a cada numero digitado,
			e possamos usar estrutura de repetição para automatizar o scan. Mas também, já converteremos o valor da variavel para inteiro, 
			para que seja possível comparar com o outro array. */
    		digitado[count] = getche();	
    		digitado[count] = digitado[count] - (int)'0';

	    }
	    
	    // Comparando os numeros digitados com os do array de numeros aleatorios.
	    
	    for (count = 0; count < streak; count++) {	
	    	if (array[count] != digitado[count]) {
	    		system("cls");
	    		printf ("Voce perdeu :c\n\nSua pontuacao foi de: %d", streak);
				Sleep(4000);
				return 0;
	    	}
	    	
	    	// Se o programa não entrou no if anterior, significa que o array digitado está correto.
	    }
	    printf ("\nParabens! \nVamos para a proxima sequencia.\n");
    	Sleep(3000);
    	system("cls");
		streak++;
	}
	
	if (streak==20)
	printf ("Voce venceu! Retiraria o meu chapeu para voce...\nse eu usasse um.");
	
    getch();
    return 0;
}
