OBJECTS = main.o pilha.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all:	main

run:	main
	./main

main:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o main

main.o:		main.c
	clang -c $(CLFLAGS) main.c

pilha.o:	pilha.c pilha.h
	clang -c $(CLFLAGS) pilha.c

clean:
	rm *.o main