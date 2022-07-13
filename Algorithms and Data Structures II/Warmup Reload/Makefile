# Para usar esse modelo de makefile genérico, que abrange
# o uso de um programa principal e uma única biblioteca,
# basta substituir todas as ocorrências de "nome do programa"
# pelo nome do seu programa principal/main arquivo.c, e o mesmo
# para "nome da biblioteca".

# O3 para compilação final, O0 para desenvolvimento e encontrar erros.

OBJECTS = warmup_reload.o filelib.o
CLFLAGS = -ggdb3 -O0 -Wall -Werror -Wextra

all:	warmup_reload

run:	warmup_reload
	./warmup_reload

warmup_reload:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o warmup_reload -lm

warmup_reload.o:		warmup_reload.c
	clang -c $(CLFLAGS) warmup_reload.c

filelib.o:	filelib.c filelib.h
	clang -c $(CLFLAGS) filelib.c

clean:
	rm *.o warmup_reload