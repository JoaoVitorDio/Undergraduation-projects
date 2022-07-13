#ifndef GENERALDATA_H_
#define GENERALDATA_H_

#define SIZE_OF_STRINGS 30
#define SIZE_OF_OPERATION 6
#define LAST_REGISTERS 10
#define NUMBER_OF_COMMAS_BY_INPUT 4

// macros que usaremos para definir qual parte da string csv será lida.
// Se enviarmos 0 como argumento, pegaremos o que está antes da primeira virgula.
// Se enviarmos 1 como argumento, pegaremos o que está após a primeira virgula.
// Se enviarmos 2 como argumento, pegaremos o que está após a 2 vírgula, e assim por diante.
#define CSV_OP 0        // operacao
#define CSV_NAME 1      // nome
#define CSV_SURNAME 2   // sobrenome
#define CSV_COURSE 3    // curso
#define CSV_GRADE 4     // nota
#define CSV_USPNUMBER 5 // contra-intuitiva a definição da macro, mas necessária.
#define CSV_OPINFO 5    // quando a operacao vem com algum dado, como por exemplo a busca (search "key")
// esse dado é obtido com a parser por meio da macro 5, ja que ocupa a mesma posicao
// do num usp na insercao

#define FILE_OF_INDEX_NAME "indexes.bin"
#define FILE_OF_DELETED "deleted.bin"

#define SIZE_OF_INDEX_HEADER 8      // tamanho do header no arquivo de indice
#define SIZE_OF_A_REGISTER 98       // int + 3 * 30 + float
#define SIZE_OF_A_INDEX 8           // usp_number (chave primária - int) + RRN (int)
#define SIZE_OF_RRN 4               // tamanho de um inteiro.

#define MAX_SIZE_OF_INPUT SIZE_OF_OPERATION + 1 + 16 + (3 * SIZE_OF_STRINGS) + NUMBER_OF_COMMAS_BY_INPUT + 1
//                          palavra da op + espaco + int + float + 3 campos + virgulas + \0


#endif // GENERALDATA_H_