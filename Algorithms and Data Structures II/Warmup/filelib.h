#define SIZE_OF_STRINGS 50

typedef struct student student_t;

// É necessário controlar uma variável armazenando o tamanho de um vetor no
// programa principal. Para que isso não fosse necessário, seria necessário encapsular
// a lista em uma outra estrutura contendo informações de "header", que acredito ser
// uma complicação adicional e por enquanto, desnecessária.

// Cria e inicializa uma lista de estudantes. Recebe como argumento
// o nome do arquivo a ser lido (para que o espaço seja otimizado)
// e retorna o endereço da primeira posicao da lista.
student_t *student_list_create(char *file_name, unsigned short int *size_of_list);

// Le todos os dados existentes no arquivo binario e os armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_all_data(char *file_name, student_t *student_list, unsigned short int size_of_list);

// Le a primeira metade do arquivo binario e os armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_first_half(char *file_name, student_t *student_list, unsigned short int size_of_list);

// Le a segunda metade do arquivo binario e os armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_last_half(char *file_name, student_t *student_list, unsigned short int size_of_list);

// Le uma determinada faixa do arquivo binario e os armazena no endereco
// passado como argumento. Recebe como argumento a posicao do primeiro
// registro a ser considerado e a posicao do ultimo registro a ser considerado.
// Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_specified_data(char *file_name, student_t *student_list,
                                       unsigned int initial_position, unsigned int final_position);

// Le um unico registro, passado como argumento, e o armazena no endereco
// passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_single_data(char *file_name, student_t *student_list, unsigned int position);

// Imprime no formato especificado pelo exercicio, todo o conteudo da lista/endereco
// passado como argumento. Recebe como argumento o tamanho do vetor para itera-lo.
unsigned short int print_data(student_t *student_list, unsigned short int size_of_list);

// Libera a memoria utilizada pelo vetor de alunos.
void student_list_destroy(student_t *student_list);