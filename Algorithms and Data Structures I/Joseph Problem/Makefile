OBJECTS = main.o josefo.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all:	main

run:	main
	./main

main:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o main

main.o:		main.c
	clang -c $(CLFLAGS) main.c

josefo.o:	josefo.c josefo.h
	clang -c $(CLFLAGS) josefo.c

clean:
	rm *.o main