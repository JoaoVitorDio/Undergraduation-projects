# Atividade:
Faça um programa em **C** que receba o número **Q** de vetores. Após isso, deve ser lido o tamanho **N** de cada um dos **Q** vetores. Em seguida, leia cada vetor. O programa deve ordenar os vetores utilizando os método de inserção e merge. Ao final deve-se imprimir o número de trocas e comparações realizadas por ambos os métodos em cada vetor, conforme a seguinte formatação: “**M N T C**”, onde **M** é o método (**I** para **inserção** e **M** para **merge**), **N** é o tamanho do vetor, **T** é o número de trocas e **C** é o número de comparações.

### Observações importantes:
Somente comparações que envolvam elementos do vetor devem ser contadas. Por exemplo, comparações do tipo i < fim não envolvem elementos do vetor, ao contrário de comparações do tipo x > vetor[i], que envolve o vetor a ser ordenado.
Considerar o conceito de "curto circuito" em C. Por exemplo, na expressão
`if (i > 0 && v[i] > x)`
, quando `i > 0` é falso, a comparação `v[i] > x` não é realizada.


### Exemplo de entrada e saída:
#### Entrada
1. 

        3
        4 8 16
        3 6 5 2
        4 8 2 1 9 0 2 3
        1 3 2 7 5 5 2 7 2 9 3 0 8 3 1 4
2. 
    
        2
		4 8
        60 77 26 184
        58 94 96 32 49 180 11 21


### Saída
1. 

        I 4 10 6
        M 4 16 5
        I 8 30 20
        M 8 48 16
        I 16 83 67
        M 16 128 48
2. 

        I 4 8 4
        M 4 16 5
        I 8 32 23
        M 8 48 16


### Como foi o desenvolvimento?
A princípio, desafiador. A primeira “lida” nos requisitos do problema pareciam super simples, com a maior parte da complexidade envolvida no desenvolvimento dos algoritmos de ordenação em si (merge e insertion), mas o primeiro raciocínio envolvendo “Como armazenar todos esses dados durante toda a ocorrência do programa para imprimir no final, e alocar memória com todos esses valores variáveis?” deu o “tapa na cara”, mostrando que não seria a tarefa mais fácil do mundo. Mas por fim, encontrei a solução envolvendo ponteiros de ponteiros e vetores bem organizados, que acabaram por deixar até que bem simples todo o controle das alocações de memória.

Não me utilizei de variáveis globais para contabilizar as trocas e comparações ocorridas dentro de cada algoritmo. O código já estava bem “fatorado” (o que foi um dos pontos que me fez refletir o quão estou melhorando e motivou a criação do “diário”. Há alguns meses atrás, ter de mexer no próprio código para adicionar alguma funcionalidade era um pesadelo, a ponto de ter vontade de criar outro do zero (tá, os códigos eram pequenos, então isso não era tão difícil) rs) e foi bem tranquilo organizar o protótipo das funções, a função em si e suas respectivas chamadas. 

Sobre o merge, temos uma relação de amor e ódio. Por julgá-lo pouco intuitivo, nunca havia nutrido muito amor por ele, o que mudou quando consegui escrevê-lo (merge recursivo) de primeira (sem erros de compilação, e de funcionamento! Sim, fiquei bem feliz com isso! Eu sonhava com o dia em que isso iria acontecer… - escrever um código inteiro, que não seja trivial, e não obter nenhum erro, logo “de cara”), e em 40 minutos… Foi sensacional. E, claro, é um dos métodos de ordenação mais eficientes em termos de complexidade de tempo existentes, além de oferecer estabilidade. 
Sobre o insertion: Ainda a ser feito.

Último comentário do dia: Achei interessante que estou desenvolvendo aos poucos uma prática que julgo muito útil, e percebi que foi relevante e bem presente durante o desenvolvimento desse código em específico: O desenvolvimento do código por partes e com testes graduais, em que é possível rodar partes do programa e testá-las, sem ter de fazer o código inteiro.

Nesse código pontual, foi interessante já ter o código funcionando e conseguir vê-lo funcionando, com o merge ordenando os vetores, enquanto ainda falta a implementação do insertion, assim como ainda faltam as contagens de troca e comparação do merge:

![Relato merge e insertion](https://user-images.githubusercontent.com/60077147/93302599-a2836600-f7d0-11ea-9686-fdbcec8c0e05.jpg)


E antes de fechar o readme e voltar à IDE para terminar o código, já percebi que há um “pulinho do gato” nesse problema: É necessário ordenar “backups” dos vetores, se não, se lidarmos apenas com ponteiros, o segundo método chamado para ordenar o vetor receberá um vetor já ordenado como argumento. Trivial? Talvez, mas só percebi enquanto escrevia o readme! auhauha

