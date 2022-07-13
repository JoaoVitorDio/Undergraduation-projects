OBJECTS = main.o josefo.o

all:	main

run:	main
	./main

main:	$(OBJECTS)
	gcc $(OBJECTS) -o main

main.o:		main.c
	gcc -c main.c

josefo.o:	josefo.c josefo.h
	gcc -c josefo.c

clean:
	rm *.o main