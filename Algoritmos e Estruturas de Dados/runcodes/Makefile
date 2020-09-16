all: substituicao

#	Makefile apenas para automatizar a compilação e exercitar o uso da ferramenta

substituicao: substituicao_string.o
	clang substituicao_string.c -ggdb3 -Wall -Werror -O0 -o substituicao

clean:
	rm substituicao

run:
	./substituicao