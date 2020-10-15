CLFLAGS = -O3 -Wall -Werror -Wextra -ggdb3

main: main.o conjuntos.o
	clang main.o conjuntos.o $(CLFLAGS) -o main

main.o: main.c conjuntos.o
	clang -c main.c

conjuntos.o: conjuntos.c conjuntos.h
	clang -c conjuntos.c

clean:
	rm *.o main