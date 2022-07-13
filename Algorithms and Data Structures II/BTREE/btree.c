/*
    Adaptado do código de:
    Henrique Gomes Zanin
    Gabriel Guimaraes Vilas Boas Marin
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "btree.h"
#include "generaldata.h"

// Prototipo de todas as funcoes desse arquivo, para que possam usar umas as outras

// Recebe o fp e o rrn de uma pagina e retorna ela lida, ja alocada em RAM
btPage *pegaPagina(long rrn, FILE *fp);
// Retrives page from file pointer. Recebe o fp apontando para a pagina a ser lida
btPage *lePaginaDoArquivo(FILE *fp);
// Writes page into file in certain rrn position
unsigned short int escrevePaginaNoArquivo(long rrn, btPage *page, FILE *fp);
// Get root RRN from header
long pegaCabecalhoArvore(FILE *fp);
// Writes root RRN in header
void escreveCabecalhoArvore(FILE *fp, long rootRRN);
// Cria uma nova pagina / arvore, inicializa seus valores apos alocar memoria
// e ja escreve no arquivo da btree com o respectivo rrn disponivel
btPage *criaArvore(FILE *fp);
// Funcao que percorre a arvore e chama a insereNoNode na pagina em que devemos inserir
promotedKey *insercaoInternaRecursiva(btPage *node, promotedKey *key, FILE *fp);

void escreve_pagina(btPage *page, FILE *fp);
// funcao que realmente insere uma promotedKey na pagina. Pode ser usada
// em nos folha ou nao. Ja lida com o overflow
promotedKey *insereNoNode(btPage *page, promotedKey *newKey, FILE *fp);

void divide_e_ajusta(btPage *page_in_left, btPage *page_in_right);

promotedKey *extrairChavePromovida(btPage *page);

promotedKey *divisaoInterna(btPage *page,FILE *fp);

btPage *criaNodeComChavePromovida(promotedKey *promoKey, FILE *fp);


// Essa funcao parte do ponto que todas as paginas no arquivo estao ocupando 4096 bytes.
long pegaRRNDisponivel(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    long rrn = (ftell(fp) - TREE_HEADER) / PAGESIZE;
    if (rrn < 0)
    {
        // significa que ainda nao escrevemos o cabecalho e estamos na raiz
        rrn = 0;
    }
    return rrn;
}

// Recebe como argumento um arquivo "de indexes" vazio ou contendo uma btree
// e retorna a pagina da btree que contem a raiz, ou cria uma e a retorna

// Depende das funcoes criaArvore, pegaCabecalhoArvore e pegaPagina
btPage *pegaOuCriaRaiz(FILE *fp) {
    // Verifica se a árvore já existe ou precisa criar uma nova
    // Se a árvore não existir, cria ela
    // Se existir, só pega o RRN da raiz no cabeçalho e carrega sua página
    // Pode ser adaptada pra inserção e busca sem precisar de 2 funções

    // vendo se a arvore ja existe: Se ja houver o cabecalho, ela existe
    fseek(fp, 0, SEEK_END);
    btPage *root;

    if (ftell(fp) == 0)
    {
        // Se estamos criando a primeira raiz, podemos assumir que o rrn eh 0
        root = criaArvore(fp);
        escreveCabecalhoArvore(fp, root -> pageRRN);

        return root;
    }

    long root_rrn = pegaCabecalhoArvore(fp);
    root = pegaPagina(root_rrn, fp);

    return root;
}

// Recebe como argumento o arquivo da arvore B e retorna a sua raiz, caso ja
// tenha sido criada.
btPage *pegaRaiz(FILE *fp) {
    fseek(fp, pegaCabecalhoArvore(fp) * PAGESIZE + TREE_HEADER, SEEK_SET);
    btPage *root = lePaginaDoArquivo(fp);

    return root;
}

// Insercao de um registro na arvore B. Recebe como argumento o endereco de
// uma estrutura record (um indice), a raiz da arvore e fp da arvore
// Parte do pressuposto que insercaoInternaRecursiva e criaNodeComChavePromovida
// funcionam devidamente.
unsigned short int insercaoArvore(record *newRecord, btPage **root, FILE *fp) {
    // Função mais abstrata de inserção

    if (newRecord == NULL)
    {
        printf("Tentativa de insercao de um registro invalido\n");
        return 0;
    }

    // Casos da Insercao:

    // 1 - Arvore vazia (situacao inicial)
        // Criamos o node raiz, preenchemos com a primeira chave e
        // inserimos as proximas chaves ate a capacidade limite do node.
        // Criamos a arvore, adicionamos e eh isso, sem verificacoes.
        // Lembrando sempre de atualizar o contador e ordenar as chaves.


    // 2 - Overflow no node raiz
        // Overflow no node mais alto => Divide ele em dois, joga para cima
        // a chave do meio e aponta o novo node raiz para os 2 filhos, que eram
        // a antiga raíz. Seta o ponteiro anterior a chave do meio, no novo node raiz
        // para a primeira metade e o segundo para a segunda metade.
        // Lembre de atualizar o no raiz, a quantia de elementos e subir apenas a chave do meio
        // A primeira chave do novo node eh a promovida para o node raiz
        // tome cuidado com numero de chaves impares na arvore


    // 3 - Insercao em nos folha
        // 3.1 - Sem overflow
            // Ocupei espaco e eh isso
            // Primeiro passo: Pesquisamos pela arvore ate encontrar o node folha
            // em que a nova chave sera inserida. Encontramos o seu lugar de ordenacao
            // e inserimos no lugar certo. Atualizamos a quantia de nodes na folha e pronto.

        // 3.2 - Com overflow
            // Preciso jogar pra cima e verificar overflow ad eternum nos niveis superiores
            // A mesma funcao de split e promocao pode ser usada nesse caso, se o codigo
            // estiver bem fatorado

    // Prepara os dados da nova chave
    // Visto que a funcao recursiva ja exige uma chave promovida,
    // prepararemos a primeira delas aqui. Chave rei porque eh promovida \o/

    promotedKey *kingKey = (promotedKey *) calloc(1, sizeof(promotedKey));
    kingKey -> key = newRecord -> key;
    kingKey -> recordRRN = newRecord -> recordRRN;
    kingKey -> childs[0] = -1;
    kingKey -> childs[1] = -1;

    // Tenta inserir recursivamente
    promotedKey *overflowedInRoot = insercaoInternaRecursiva(*root, kingKey, fp);
    libera_node(*root);

    // Se tiver chave promovida no final da recursão, é que existe nova raiz
    // Chama as funções pra criar nova raiz e atualizar o cabeçalho
    if (overflowedInRoot != NULL)
    {
        // Houve overflow nas paginas abaixo e foi propagada ate a raiz
        btPage *newRoot = criaNodeComChavePromovida(overflowedInRoot, fp);
        escreveCabecalhoArvore(fp, newRoot -> pageRRN);

        free(overflowedInRoot);

        libera_node(newRoot);
    }

    if (kingKey != NULL)
    {
        free(kingKey);
    }

    long root_rrn = pegaCabecalhoArvore(fp);
    *root = pegaPagina(root_rrn, fp);

    return 1;
}

// Returns rrn if key exist else return -1
// Essa funcao depende da pegaPagina e da pegaRaiz / Cria Raiz
long buscaArvore(btPage *node, int key, FILE *fp) {
    // Procura no nó atual se a chave existe
    // Se não existir, tenta procurar no filho adequado, recursivamente
    // Se encontrar a chave, retorna RRN dela
    // Se não encontrar (chegar num nó folha e não estiver lá), retorna -1

    if (node -> numberOfKeys == 0) {
        return -1;
    }

    int index = 0;

    while (index < node -> numberOfKeys && key > node -> records[index].key) {
        index++;
    }

    if (node -> records[index].key == key) {
        int recordRRN = node -> records[index].recordRRN;

        return recordRRN;
    }

    int childRRN = node -> childs[index];

    btPage *page = pegaPagina(childRRN, fp);
    long rrn = buscaArvore(page, key, fp);

    libera_node(page);

    return rrn;
}

// Retrives page from file pointer. Recebe o fp apontando para a pagina a ser lida
btPage *lePaginaDoArquivo(FILE *fp) {
    // Aloca espaço para carregar página
    btPage *page = (btPage *) calloc(1, sizeof(btPage));
    page -> records = (record *) calloc(MAXKEYS, sizeof(record));
    page -> childs = (long *) calloc(MAXKEYS + 1, sizeof(long));

    // Lê dados da página do arquivo
    // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    for (int i = 0; i < MAXKEYS; i++)
    {
        fread(&page -> records[i].key, sizeof(int), 1, fp);
        fread(&page -> records[i].recordRRN, sizeof(long), 1, fp);
    }
    fread(page -> childs, sizeof(long), MAXKEYS + 1, fp);

    fread(&page -> numberOfKeys, sizeof(short), 1, fp);
    fread(&page -> isLeaf, sizeof(char), 1, fp);
    fread(&page -> pageRRN, sizeof(long), 1, fp);

    return page;
}

void escreve_pagina(btPage *page, FILE *fp)
{
    // Nao posso usar sizeof(records) porque eh bugado : D
    for (int i = 0; i < MAXKEYS; i++)
    {
        fwrite(&page -> records[i].key, sizeof(int), 1, fp);
        fwrite(&page -> records[i].recordRRN, sizeof(long), 1, fp);
    }
    fwrite(page -> childs, sizeof(long), MAXKEYS + 1, fp);

    fwrite(&page -> numberOfKeys, sizeof(short), 1, fp);
    fwrite(&page -> isLeaf, sizeof(char), 1, fp);
    fwrite(&page -> pageRRN, sizeof(long), 1, fp);

    // Preenchendo o espaco restante da pagina para ocupar 4096 bytes
    char *fill_empty_space = (char *) calloc(FREE_SPACE_ON_PAGE, sizeof(char) );
    fwrite(fill_empty_space, sizeof(char), FREE_SPACE_ON_PAGE, fp);
    free(fill_empty_space);

    fflush(fp);
}

// Writes page into file in certain rrn position
unsigned short int escrevePaginaNoArquivo(long rrn, btPage *page, FILE *fp) {
    // Verifica se está tudo ok com os dados
    // Encontra local para escrita baseado no RRN
    // Escreve dados
    // Atualiza valor de espaço livre na página
    // Dica: você pode criar uma função que só lida com a escrita dos dados e chamar aqui
    if (page == NULL || fp == NULL || page -> records == NULL ||
        page -> childs == NULL )
    {
        return 0;
    }

    // Movendo para o rrn especificado...
    fseek(fp, TREE_HEADER + rrn * PAGESIZE, SEEK_SET);
    escreve_pagina(page, fp);

    return 0;
}

// Get page by rrn. Recebe o fp em qualquer posicao.
btPage *pegaPagina(long rrn, FILE *fp) {
    // Recupera uma página baseado no RRN
    // Procura e carrega seus dados

    fseek(fp, TREE_HEADER + rrn * PAGESIZE, SEEK_SET);
    btPage *page = lePaginaDoArquivo(fp);

    return page;
}

// Get root RRN from header
long pegaCabecalhoArvore(FILE *fp) {
    // Carrega o cabeçalho da árvore, que está no início do arquivo

    fseek(fp, 0, SEEK_SET);
    long root_rrn = 0;

    fread(&root_rrn, sizeof(long), 1, fp);

    return root_rrn;
}

// Writes root RRN in header
void escreveCabecalhoArvore(FILE *fp, long rootRRN) {
    // Calcula espaço livre e escreve no cabeçalho da árvore, junto com o RRN do nó raíz

    fseek(fp, 0, SEEK_SET);

    char *fill_empty_space = (char *) calloc(TREE_HEADER, sizeof(char) );

    // size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream);
    fwrite(fill_empty_space, TREE_HEADER, 1, fp);

    // ja preenchemos o espaco que precisava, agora eh so colocar o rrn da raiz
    fseek(fp, 0, SEEK_SET);
    fwrite(&rootRRN, sizeof(long), 1, fp);

    free(fill_empty_space);
    fflush(fp);
}

// Parte do ponto que pegaRRNDisponivel, escrevePaginaNoArquivo e
// escreveCabecalhoArvore estao funcionando bem
btPage *criaArvore(FILE *fp) {
    btPage *root = (btPage *) calloc(1, sizeof(btPage));

    root -> records = (record *) calloc(MAXKEYS, sizeof(record));
    root -> childs = (long *) calloc(MAXKEYS + 1, sizeof(long));

    root -> numberOfKeys = 0;
    root -> isLeaf = 1;

    // setando todos os valores inicializados para -1, visto que o 0
    // default do calloc pode ser um rrn valido ou o rrn de uma pagina filha
    for (int i = 0; i < MAXKEYS; i++)
    {
        root -> records[i].key = -1;
        root -> records[i].recordRRN = -1;
        root -> childs[i] = -1;
    }
    root -> childs[MAXKEYS] = -1;

    long root_rrn = pegaRRNDisponivel(fp);
    root -> pageRRN = root_rrn;
    escrevePaginaNoArquivo(root_rrn, root, fp);

    return root;
}

//  ************ Funcoes recomendadas no modelo do Leo  *************

// Parte do pressuposto que a funcao divisaoInterna e escrevePaginaNoArquivo funcionam
promotedKey *insereNoNode(btPage *page, promotedKey *newKey, FILE *fp) {

    int index = 0;
    // Procura local pra inserir nova chave na página
    while (index < page -> numberOfKeys && newKey -> key > page -> records[index].key)
    {
        index++;
    }

    // Grato, monitoria.
    memmove(&page -> records[index + 1], &page -> records[index], ( (page -> numberOfKeys) - index ) * sizeof(record) );
    memmove(&page -> childs[index + 1], &page -> childs[index], ( (page -> numberOfKeys) - index + 1 ) * sizeof(long) );
    page -> numberOfKeys++;

    page -> records[index].key = newKey -> key;
    page -> records[index].recordRRN = newKey -> recordRRN;

    page -> childs[index] = newKey -> childs[0];
    page -> childs[index + 1] = newKey -> childs[1];

    // Se não couber, splitta ele
    // Para que consigamos adicionar um registro na pagina antes de splitá-lo, sem segFault,
    // ou temos de ter um espaço a mais alocado, que eh uma opcao, ou, splitar assim que enche
    // ao inves de deixar explodir. Usamos a segunda opcao por ser mais pratica e controlavel.
    promotedKey *kingKey = NULL;
    if (page -> numberOfKeys == MAXKEYS)
    {
        kingKey = divisaoInterna(page, fp);

        // A pagina ja foi escrita e podemos retornar direto daqui ao inves de perder tempo
        return kingKey;
    }

    // Escreve dados na página
    escrevePaginaNoArquivo(page -> pageRRN, page, fp);

    return kingKey;
}

// Extract a promoted key from page
promotedKey *extrairChavePromovida(btPage *page) {
    // Aloca espaço pra chave
    promotedKey *kingKey = (promotedKey *) calloc(1, sizeof(promotedKey));

    // Tira ela da página
    // Atualiza dados da página (filho, número de chaves, etc)
    kingKey -> key = page -> records[0].key;
    kingKey -> recordRRN = page -> records[0].recordRRN;


    memmove(&page -> records[0], &page -> records[1], ( page -> numberOfKeys - 1 ) * sizeof(record) );
    // setando a ultima chave que agora foi uma posicao para tras para -1, evitando possiveis erros
    page->records[page -> numberOfKeys - 1].key = -1;
    page->records[page -> numberOfKeys - 1].recordRRN = -1;

    memmove(&page -> childs[0], &page -> childs[1], ( page -> numberOfKeys ) * sizeof(long) );
    // setando o ultimo filho que agora foi uma posicao para tras para -1, evitando possiveis erros
    page->childs[page -> numberOfKeys] = -1;

    (page -> numberOfKeys)--;

    return kingKey;
}

// Split node and writes into file
promotedKey *divisaoInterna(btPage *page, FILE *fp) {

    // Cria o novo nó (faça numa função auxiliar pois é complexo)
    btPage *newPage = criaArvore(fp);

    // Divide a pagina
    divide_e_ajusta(page, newPage);

    // Extrai a chave promovida e atualiza os filhos da chave
    promotedKey *kingKey = extrairChavePromovida(newPage);

    kingKey -> childs[0] = page -> pageRRN;
    kingKey -> childs[1] = newPage -> pageRRN;

    // Escreve a página nova e a que foi dividida (com suas atualizações) no arquivo
    escrevePaginaNoArquivo(page -> pageRRN, page, fp);
    escrevePaginaNoArquivo(newPage -> pageRRN, newPage, fp);

    // Apenas a pagina da direita foi criada aqui. A pagina da esquerda pode ser
    // a raiz e a responsabilidade eh de outras funcoes.
    libera_node(newPage);
    // libera_node(page);

    return kingKey;
}

// Ao fim da execucao da funcao, page_in_left possui metade arredondada para baixo
// registros e page_in_right possui metade arredondada para cima.
// O proximo passo eh extrair a chave promovida, ou seja, a primeira chave
// da pagina a direita
void divide_e_ajusta(btPage *page_in_left, btPage *page_in_right) {
    // Encontra a posição do meio das chaves
    int middle_position = (page_in_left -> numberOfKeys) / 2;

    // Copia metade das chaves pra página nova
    int registers_moved = page_in_left -> numberOfKeys - middle_position;

    // Atualiza os filhos de ambas as páginas
    // void *memmove(void *dest, const void *src, size_t n);
    memmove(page_in_right -> records, &page_in_left -> records[middle_position], registers_moved * sizeof(record));
    memmove(page_in_right -> childs, &page_in_left -> childs[middle_position], (registers_moved + 1) * sizeof(long));

    // Limpa elas do nó antigo
    for (int i = middle_position; i < MAXKEYS; i++)
    {
        page_in_left -> records[i].key = -1;
        page_in_left -> records[i].recordRRN = -1;
    }
    for (int i = middle_position + 1; i <= MAXKEYS; i++)
    {
        page_in_left -> childs[i] = -1;
    }

    // Em uma pagina cheia, todos os filhos possuem ponteiros (segundo a aula de insercao O_O)
    page_in_right -> isLeaf = page_in_left -> isLeaf;

    // Atualiza o número de chaves de ambas
    page_in_left -> numberOfKeys -= registers_moved;
    page_in_right -> numberOfKeys = registers_moved;

    // o campo pageRRN ja foi setado durante a criacao, feita antes dessa funcao ser chamada
}


// Used if promotions reaches root
btPage *criaNodeComChavePromovida(promotedKey *promoKey, FILE *fp) {
    // Pode reusar função que cria página nova e adicionar somente especificidades

    // Se promoção cria estrutura para nova raiz,
    // Aloca espaço para ela
    btPage *newRoot = criaArvore(fp);

    // Salva dados da chave promovida na nova raiz
    // Nao precisamos verificar se houve chave promovida porque acabamos de criar
    // a pagina, logo, esta vazia. Eh uma nova raiz
    insereNoNode(newRoot, promoKey, fp);
    newRoot -> isLeaf = 0;

    // ja escreve a nova raiz no arquivo
    escrevePaginaNoArquivo(newRoot -> pageRRN, newRoot, fp);
    // atualiza os filhos deste novo nó/página
    // Ja sao atualizados durante o split que aconteceu antes de chegar aqui

    return newRoot;
}

// Recursive insertion
promotedKey *insercaoInternaRecursiva(btPage *node, promotedKey *key, FILE *fp)
{
    // PS: SEMPRE INSERIMOS NOS NODE FOLHAS

    promotedKey *kingKey = NULL;

    // Se nó a ser inserido a chave é folha, tenta inserir
    if (node -> isLeaf == 1)
    {
        kingKey = insereNoNode(node, key, fp);

        // Caso a inserção crie uma promoção, precisa retornar a chave promovida para a recursão
        return kingKey;
    }

    // Se não for nó folha, procura qual sub-árvore seguir para inserir numa folha
    unsigned short int index = 0;
    while (index < node -> numberOfKeys && key -> key > node -> records[index].key)
    {
        index++;
    }

    btPage *childPage = NULL;
    // Encontrar a posição correta e descer para filho à esquerda se a chave for menor
    if (key -> key < node -> records[index].key)
    {
        // Chamar a inserção recursiva pro filho escolhido
        childPage = pegaPagina(node -> childs[index], fp);
        kingKey = insercaoInternaRecursiva(childPage, key, fp);
    }
    // Se tivermos chegado ao ultimo elemento, meu index ja esta apontando para o filho
    // direito da chave anterior
    else if (index == node -> numberOfKeys)
    {
        // Chamar a inserção recursiva pro filho escolhido
        childPage = pegaPagina(node -> childs[index], fp);
        kingKey = insercaoInternaRecursiva(childPage, key, fp);
    }
    // E descer à direita se for maior
    else
    {
        // Chamar a inserção recursiva pro filho escolhido
        childPage = pegaPagina(node -> childs[index + 1], fp);
        kingKey = insercaoInternaRecursiva(childPage, key, fp);
    }

    // Alguma pagina foi pega no childPage e precisamos libera-la. Nao
    // precisamos nos preocupar com ler algum rrn -1 porque se fosse folha,
    // a funcao nao chegaria ate aqui
    libera_node(childPage);

    // Se a inserção recursiva retornar uma chave promovida, precisa tentar
    // inserir essa chave promovida no nó atual.
    if (kingKey != NULL)
    {
        promotedKey *backupPromotedKey = insereNoNode(node, kingKey, fp);

        free(kingKey);
        return backupPromotedKey;
    }

    // Retornar chave promovida ou um valor NULL se não houve promoção
    return kingKey;
}


void libera_node(btPage *root)
{
    free(root -> records);
    free(root -> childs);
    free(root);
}