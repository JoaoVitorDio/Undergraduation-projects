OBJECTS = main.o lista.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all:	main

run:	main
	./main

main:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o main

main.o:		main.c
	clang -c $(CLFLAGS) main.c

lista.o:	lista.c lista.h
	clang -c $(CLFLAGS) lista.c

clean:
	rm *.o main