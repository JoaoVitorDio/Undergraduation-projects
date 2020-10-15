# Para usar esse modelo de makefile genérico, que abrange
# o uso de um programa principal e uma única biblioteca,
# basta substituir todas as ocorrências de nome_do_programa
# pelo nome do seu programa principal/main arquivo.c, e o mesmo
# para o nome da biblioteca.

OBJECTS = nome_do_programa.o nome_da_biblioteca.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all:	nome_do_programa

run:	nome_do_programa
	./nome_do_programa

nome_do_programa:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o nome_do_programa

nome_do_programa.o:		nome_do_programa.c
	clang -c $(CLFLAGS) nome_do_programa.c

nome_da_biblioteca.o:	nome_da_biblioteca.c nome_da_biblioteca.h
	clang -c $(CLFLAGS) nome_da_biblioteca.c

clean:
	rm *.o nome_do_programa