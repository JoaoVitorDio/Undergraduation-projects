# Para usar esse modelo de makefile genérico, que abrange
# o uso de um programa principal e uma única biblioteca,
# basta substituir todas as ocorrências de "nome do programa"
# pelo nome do seu programa principal/main arquivo.c, e o mesmo
# para "nome da biblioteca".

# O3 para compilação final, O0 para desenvolvimento e encontrar erros.

OBJECTS = indice_primario.o filelib.o generallib.o
CLFLAGS = -ggdb3 -O0 -Wall -Werror -Wextra

all:	indice_primario

run:	indice_primario
	./indice_primario

indice_primario:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o indice_primario -lm

indice_primario.o:		indice_primario.c
	clang -c $(CLFLAGS) indice_primario.c

filelib.o:	filelib.c filelib.h generallib.c generallib.h generaldata.h
	clang -c $(CLFLAGS) filelib.c

generallib.o: generallib.c generallib.h generaldata.h
	clang -c $(CLFLAGS) generallib.c

clean:
	rm *.o indice_primario *.bin