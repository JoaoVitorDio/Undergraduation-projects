conversor: conversor.o pilha.o
	clang conversor.o pilha.o -ggdb3 -Wall -lm -O3 -o conversor

conversor.o: conversor.c pilha.o
	clang -c conversor.c

pilha.o: pilha.c pilha.h
	clang -c pilha.c

clean:
	rm *.o conversor