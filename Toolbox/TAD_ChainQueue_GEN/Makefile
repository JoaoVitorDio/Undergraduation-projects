OBJECTS = main.o fila.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all:	main

run:	main
	./main

main:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o main

main.o:		main.c
	clang -c $(CLFLAGS) main.c

fila.o:	fila.c fila.h
	clang -c $(CLFLAGS) fila.c

clean:
	rm *.o main