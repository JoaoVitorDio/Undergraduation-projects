# Para usar esse modelo de makefile genérico, que abrange
# o uso de um programa principal e uma única biblioteca,
# basta substituir todas as ocorrências de "nome do programa"
# pelo nome do seu programa principal/main arquivo.c, e o mesmo
# para "nome da biblioteca".

# Autor: Joao Vitor Diógenes.

# O3 para compilamento final, O0 para desenvolvimento e encontrar erros.

OBJECTS = main.o dictionary.o

all:	main

run:	main
	./main

main:	$(OBJECTS)
	gcc $(OBJECTS) -o main

main.o:		main.c
	gcc -c main.c

dictionary.o:	dictionary.c dictionary.h
	gcc -c dictionary.c

clean:
	rm *.o main