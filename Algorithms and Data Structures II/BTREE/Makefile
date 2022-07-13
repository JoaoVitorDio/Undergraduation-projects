# O3 para compilação final, O0 para desenvolvimento e encontrar erros.

OBJECTS = main.o btree.o auxiliar.o

all:	main

run:	main
	./main

main:	$(OBJECTS)
	gcc $(OBJECTS) -o main -lm

main.o:		main.c
	gcc -c main.c

btree.o:	btree.c btree.h auxiliar.c auxiliar.h generaldata.h
	gcc -c btree.c

auxiliar.o: auxiliar.c auxiliar.h generaldata.h
	gcc -c auxiliar.c

clean:
	rm *.o main *.bin *.out