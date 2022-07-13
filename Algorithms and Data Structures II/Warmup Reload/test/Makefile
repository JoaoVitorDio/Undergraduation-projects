# Para usar esse modelo de makefile genérico, que abrange
# o uso de um programa principal e uma única biblioteca,
# basta substituir todas as ocorrências de "nome do programa"
# pelo nome do seu programa principal/main arquivo.c, e o mesmo
# para "nome da biblioteca".

# O3 para compilação final, O0 para desenvolvimento e encontrar erros.

OBJECTS = warmup_reload.o filelib.o

all:	warmup_reload

run:	warmup_reload
	./warmup_reload

warmup_reload:	$(OBJECTS)
	gcc $(OBJECTS) -o warmup_reload -lm

warmup_reload.o:		warmup_reload.c
	gcc -c warmup_reload.c

filelib.o:	filelib.c filelib.h
	gcc -c filelib.c

clean:
	rm *.o registers_in_binary.bin warmup_reload