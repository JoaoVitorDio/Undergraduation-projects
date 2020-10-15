OBJECTS = main.o pilha.o

all:	main

run:	main
	./main

main:	$(OBJECTS)
	gcc $(OBJECTS) -o main

main.o:	main.c
	gcc -c main.c

pilha.o:	pilha.c pilha.h
	gcc -c pilha.c

clean:
	rm *.o main