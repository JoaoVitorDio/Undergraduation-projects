OBJECTS = verifica_parenteses.o pilha.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all:	verifica_parenteses

run:	verifica_parenteses
	./verifica_parenteses

verifica_parenteses:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o verifica_parenteses

verifica_parenteses.o:		verifica_parenteses.c
	clang -c $(CLFLAGS) verifica_parenteses.c

pilha.o:	pilha.c pilha.h
	clang -c $(CLFLAGS) pilha.c

clean:
	rm *.o verifica_parenteses