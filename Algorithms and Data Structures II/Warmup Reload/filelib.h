#define SIZE_OF_STRINGS 50
#define LAST_REGISTERS 10
#define NUMBER_OF_COMMAS_BY_INPUT 3
#define MAX_SIZE_OF_INPUT 8 + (2 * SIZE_OF_STRINGS) + NUMBER_OF_COMMAS_BY_INPUT

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


// Funcoes do warmup reload

// Le os ultimos 10 (ou o numero definido) registros do arquivo binario e os armazena
// no endereco passado como argumento. Retorna 1 em sucesso e 0 caso contrario.
unsigned short int read_last_data(char *file_name, student_t *student_list);

// Recebe o nome de um arquivo e uma string csv como argumento. Armazena as informacoes contidas
// na string_csv no formato student_t no arquivo binário especificado, de forma a ser lida
// posteriormente pelas demais funcoes do programa. Retorna 1 em sucesso, 0 caso contrário.
unsigned short int write_string_data(char *file_name, char *string_csv);

// funcao que retira o \n de uma string, caso haja algum
void sanitize_string(char *str);

void clean_old_data(char *file_name);