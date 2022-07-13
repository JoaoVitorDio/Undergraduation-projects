# Para usar esse modelo de makefile genérico, que abrange
# o uso de um programa principal e uma única biblioteca,
# basta substituir todas as ocorrências de "nome do programa"
# pelo nome do seu programa principal/main arquivo.c, e o mesmo
# para "nome da biblioteca".

# O3 para compilação final, O0 para desenvolvimento e encontrar erros.

OBJECTS = warmup.o filelib.o

all:	warmup

run:	warmup
	./warmup

warmup:	$(OBJECTS)
	gcc $(OBJECTS) -o warmup -lm

warmup.o:		warmup.c
	gcc -c warmup.c

filelib.o:	filelib.c filelib.h
	gcc -c filelib.c

clean:
	rm *.o warmup