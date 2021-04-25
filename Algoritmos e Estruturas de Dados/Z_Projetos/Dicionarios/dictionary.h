/*  Para o funcionamento do TAD, é necessário que o programa principal gere uma seed
    aleatória para que a skiplist funcione e tenha proveito de sua eficiencia ideal.
    Para isso, utilize a biblioteca time.h e stdlib.h, com um comando "srand(time(NULL));"
    em algum lugar do programa antes de utilizar alguma função do TAD.              */


#define SIZE_OF_VERBETE 51
#define SIZE_OF_DEFINITION 141

typedef struct skiplist dictionary_t;

// aloca memoria para um dicionario e retorna seu endereço ao usuario
dictionary_t *dictionary_create();

// insere a palavra passada como argumento no dicionário passado como argumento
// (com a respectiva definicao). Retorna 1 em caso de sucesso, 0 caso contrário
// (palavra já inserida, por exemplo)
unsigned short int dictionary_insert(dictionary_t *dic, char *word, char *definition);

// remove a palavra passada como argumento do dicionário passado como argumento.
// retorna 1 em caso de sucesso, 0 caso contrário (palavra não existente no dicionario)
unsigned short int dictionary_remove(dictionary_t *dic, char *word);

// altera a definicao da palavra word para a definicao passada para correction, no dicionario
// passado como argumento. Retorna 1 caso a operação seja bem sucedida, 0 caso não.
unsigned short int dictionary_change(dictionary_t *dic, char *word, char *correction);

// imprime a palavra passada como argumento e sua definicao. Retorna 1 caso a
// operacao seja bem sucedida e 0 caso contrario (palavra nao encontrada, por exemplo)
unsigned short int dictionary_print_word(dictionary_t *dic, char *word);

// imprime todas as palavras no dicionario dic que iniciem o caracter 'letter'
// retorna 1 caso a impressao seja bem sucedida e 0 caso nao haja nenhuma palavra
// com a letra inicial recebida
unsigned short int dictionary_print_letter(dictionary_t *dic, char letter);

// libera a funcao usada pelo dicionario
void dictionary_destroy(dictionary_t *dic);

