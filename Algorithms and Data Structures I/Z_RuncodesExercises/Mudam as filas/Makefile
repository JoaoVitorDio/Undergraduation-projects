OBJECTS = main.o fila.o

all:	main

run:	main
	./main

main:	$(OBJECTS)
	gcc $(OBJECTS) -o main

main.o:		main.c
	gcc -c -ggdb3 main.c

fila.o:	fila.c fila.h
	gcc -c -ggdb3 fila.c

clean:
	rm *.o main