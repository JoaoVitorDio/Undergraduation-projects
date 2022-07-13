#ifndef FILELIB_H_
#define FILELIB_H_


// Recebe o nome de um arquivo e uma string em csv como argumento. Armazena
// o registro contido na string, no arquivo de nome passado como argumento,
// utilizando-se do arquivo de indices primarios indexes.bin. Retorna 1 caso sucesso
// e 0 caso contrário
unsigned short int insert_data_in_file(char *file_name, char *string_csv);

// Recebe uma string como argumento para armazenar a (index_ésima + 1) palavra
// no endereco "parsed_word"
unsigned short int parser_csv_string(char *parsed_word, char *string_to_parse, unsigned short int index);

// Recebe o nome do arquivo e uma chave. Procura pela chave passada no arquivo recebido
// de nome recebido como argumento (utilizando indexação primária e busca binária).
// Imprime os dados da key encontrada em caso de sucesso. Retorna 1 em sucesso e 0 caso contrário.
unsigned short int search(char *file_name, int key);

// Recebe o nome de um arquivo e um numero_usp como argumentos. Deleta o registro
// do estudante com determinado numero usp do arquivo, caso exista. Retorna 1 caso a remoção
// seja bem sucedida. 0 caso contrário.
unsigned short int delete_register(char *file_name, int key_to_delete);

// Imprime todos os registros do arquivo de registros passado como argumento, independentemente
// de terem sido removidos logicamente ou não.
unsigned short int sequential_print(char *file_name);

#endif // FILELIB_H_