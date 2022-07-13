OBJECTS = main.o merge.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all:	main

run:	main
	./main

main:	$(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -lm -o main

main.o: main.c
	clang $(CLFLAGS) -c main.c

merge.o:	merge.c merge.h
	clang $(CLFAGS) -c merge.c

clean:
	rm *.o main