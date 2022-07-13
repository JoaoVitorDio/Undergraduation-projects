# Para usar esse modelo de makefile genérico, que abrange
# o uso de um programa principal e uma única biblioteca,
# basta substituir todas as ocorrências de "nome do programa"
# pelo nome do seu programa principal/main arquivo.c, e o mesmo
# para "nome da biblioteca".

# O3 para compilação final, O0 para desenvolvimento e encontrar erros.

OBJECTS = main.o redblack.o

all:	main

run:	main
	./main

main:	$(OBJECTS)
	gcc $(OBJECTS) -o main

main.o:		main.c
	gcc -c main.c

redblack.o:	redblack.c redblack.h
	gcc -c redblack.c

clean:
	rm *.o main