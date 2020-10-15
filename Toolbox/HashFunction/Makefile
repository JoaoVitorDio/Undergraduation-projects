OBJECTS = example.o MurmurHash3.o
CLFLAGS = -ggdb3 -O3 -Wall -Werror -Wextra

all: example

run: example
	./example

example: $(OBJECTS)
	clang $(OBJECTS) $(CLFLAGS) -o example

example.o: example.c
	clang -c $(CLFLAGS) example.c

MurmurHash3.o: MurmurHash3.c MurmurHash3.h
	clang -c $(CLFLAGS) MurmurHash3.c

clean:
	rm *.o example