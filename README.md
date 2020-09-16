# Projetos em Software - Graduação :mortar_board: :mortar_board:

### O que é esse repositório?

É um repositório das soluções *sobretudo, na linguagem C* elaboradas pelo estudante João Vitor D. durante o curso **Bacharelado em Sistemas de Informação** no [Instituto de Ciências Matemáticas e de Computação](https://www.icmc.usp.br/ "Instituto de Ciências Matemáticas e de Computação") da **[Universidade de São Paulo](https://www5.usp.br/ "Universidade de São Paulo")**.

### Por que?

No mercado de tecnologia, é super interessante para aqueles que desejam crescer dentro dele que sua evolução seja relevante, constante, e claro, que seus passos sejam documentados. :star2: :rocket: 

Concomitantemente, para que as oportunidades possam aparecer e se encontrar, seja ao indivíduo, seja às potenciais iniciativas que têm demanda de determinado profissional, é necessário que os envolvidos deixem “pegadas digitais :paw_prints: :paw_prints: ” (aos termos do criador de conteúdo @filipedeschamps), ou seja, mostrar ao mundo quem você é, o que você faz, e como você faz. Afinal, como uma empresa com a ideia que se encaixa com o seu perfil poderia adivinhar que você existe e tem o perfil que a empresa precisa, se ela mal sabe que você existe?!

![highresrollsafe](https://user-images.githubusercontent.com/60077147/93292332-b8d2f700-f7bb-11ea-97f9-c858a973a602.jpg)



Nós, desenvolvedores em geral, temos uma forte ajudinha (*de nós mesmos*) com o [GitHub](https://github.com/ "GitHub"). A plataforma permite que compartilhemos o que estamos fazendo, ~~além de todas as inúmeras ferramentas úteis de versionamento de código (que não deixam de ser o principal motivo de uso da plataforma - creio eu)~~, ou seja, podemos nos expor **ao mundo** sem praticamente qualquer custo, que não seja nosso próprio tempo e disposição em aprender e apresentar projetos e ideias.

**Sendo assim**... tive a ideia de começar a de fato documentar minha trilha pela carreira de tecnologia, não só por meio dos projetos que eu já procurava manter atualizados no GitHub, mas também, anotando, descrevendo e relatando a evolução que sinto durante esse caminho! ~~(Epifanias aleatórias que ocorrem enquanto “codamos”, sabem como é)~~. E tudo será documentado nesse repositório! (Ao menos, no que tange projetos acadêmicos rs) 

¯\\_(ツ)_/¯

### Como está organizado?

~~Supondo a já familiaridade com o github:~~:
O repositório está dividido por matérias (não há um repositório para cada matéria do curso, visto que nem todas são voltadas ao desenvolvimento de software). As matérias do curso voltadas ao estudo da ciência da computação e consequente familiarização do aluno com o desenvolvimento de software, ~~até agora~~, foram/são: [Introdução à Ciência da Computação (ICC)](https://github.com/JoaoVitorDio/Projetos-em-C-Graduacao-/tree/master/Introdu%C3%A7%C3%A3o%20%C3%A0%20Ci%C3%AAncia%20da%20Computa%C3%A7%C3%A3o%201 "Introdução à Ciência da Computação (ICC)") e [Algoritmos e Estruturas de Dados (ALGED)](https://github.com/JoaoVitorDio/Projetos-em-C-Graduacao-/tree/master/Algoritmos%20e%20Estruturas%20de%20Dados "Algoritmos e Estruturas de Dados (ALGED)").

No diretório [ICC1](https://github.com/JoaoVitorDio/Projetos-em-C-Graduacao-/tree/master/Introdu%C3%A7%C3%A3o%20%C3%A0%20Ci%C3%AAncia%20da%20Computa%C3%A7%C3%A3o%201 "ICC1"), estão os primeiros passinhos de um aluno que definitivamente não sabia absolutamente nada de programação, quem dirá da linguagem C. Os exercícios estão em ordem crescente de andamento do curso e consequente aprendizado de novas ferramentas e métodos. ~~Sim, os primeiros exercícios dão vergonha, mas nem por isso são menos importantes! Sem eles, eu não estaria aqui, então, que públicos estejam... rs~~ Não há diretório das aulas 1 a 7 porque foram aulas expositivas e teóricas, em pseudocódigo e introdução aos conceitos, como variáveis, compiladores, montadores, fluxos de código e o básico do básico da lógica envolvida na programação.

No final de ICC1 e começo do segundo semestre - Começo das disciplinas de ALGED e ICC2 - passei a utilizar um [ambiente Unix baseado em nuvem para o desenvolvimento](https://ide.cs50.io/ "ambiente Unix baseado em nuvem para o desenvolvimento"), assim como ferramentas mais interessantes para debuggar e acompanhar o funcionamento dos códigos *-ggdb e Valgrind-* e consequentemente contato mais próximo com a `linha de comando` e afins. Visto que estou no segundo semestre, os projetos mais recentes estão nesses repositórios.

### Como utilizo alguma das soluções?

Por mais que os projetos desenvolvidos até agora, em sua maioria, não tenham grande aplicação prática e comercial, foram super importantes e alguns consideravelmente desafiadores do ponto de vista do **desenvolvimento da lógica de organizar as informações e elaborar uma sequência de passos que faça sentido a uma máquina** (o que é super relevante ao meu ver, já que, infelizmente ~~ou felizmente~~), a vida não é assim:

![b9d6de8262241bf9ac45ea28360a426f](https://user-images.githubusercontent.com/60077147/93294909-3d287880-f7c2-11ea-9b07-211c1b823d98.jpg)



Alguns possuem utilidade na matemática, como o algoritmo para cálculo da raíz de newton, ou a "impressora de números primos", ou até mesmo o programa gerador da sequência de fibonacci. Alguns - na parte do estudo de structs e gerenciamento de arquivos, por exemplo - são pequenos sistemas gerenciais.

Caso tenha interesse em executar qualquer uma das soluções aqui presente, é necessário compilar o `código .c` (no caso de programas de arquivo único. Alguns requerem linkedição e uso da ferramenta CMake - O makefile estará no mesmo diretório que o arquivo e mais abaixo está a explicação de como funciona).

Para isso, caso já tenhas instalado o gcc e os pacotes de desenvolvimento, basta seguir o guia...:

    if (arquivo.c == Único arquivo do diretório())
    {
    	printf("Digite no seu terminal linux, dentro do diretório em que o programa foi baixado:\n");
    	$ gcc nome_do_programa.c -o nome_do_programa
    	printf("Surgirá magicamente um arquivo executável no diretório atual: 'nome_do_programa'\n");
    	printf("Para executá-lo, digite:\n);
    	$ ./nome_do_programa
    }

Caso utilizes o windows, ~~ou simplesmente seja mais prático~~, recomendo o uso de um ambiente em nuvem baseado em ubuntu para fazer o processo: o [Repl.it](https://repl.it/ "Repl.it").
Basta criar a conta, criar um repositório e, dentro dele, executar exatamente os mesmos passos descritos acima (ir ao diretório em que colocaste o arquivo - dentro do [Repl.it](https://repl.it/ "Repl.it") - com o terminal e compilar/rodar o executável).

Se o diretório que contém a solução que deseja utilizar possuir mais de um arquivo.c, trata-se de um programa um pouco mais estruturado e provavelmente mais complexo, no sentido de depender de mais funções e afins.
Nesses casos, cada um desses diretórios constará também um arquivo de nome "*Makefile*", que é o responsável por automatizar o processo de compilação/linkedição/montagem e execução. Basta dar upload/transferir todos os arquivos do diretório do github para o repositório do repl.it e digitar:

    $ make all
    $ make run

### Por fim...

Qualquer dúvida, seja sobre o repositório e utilização de algo aqui, ou interesse no curso e coisas do tipo, meu email de contato está no perfil do GitHub! 

Sugestões de melhorias nos códigos (ainda que muitos estejam vergonhosos "propositalmente" e poderiam estar muito melhor projetados e desenvolvidos, como foram ~~em sua maioria~~, os primeiros projetos e exercícios que desenvolvi, achei mais interessante deixá-los como estavam para retratar a trilha de maneira mais real, ao invés de consertar códigos que poucas pessoas - ou ninguém - usaria) são totalmente bem vindas e peço que se sintam totalmente à vontade para dar-lhe o pull request!
