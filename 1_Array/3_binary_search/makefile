main: main.o binary_search.o
	gcc -Wall -o main main.o binary_search.o
main.o: main.c
	gcc -Wall -c main.c
main.o: binary_search.h
binary_search.o: binary_search.c
	gcc -Wall -c binary_search.c

.PHONY: clean
clean:
	rm -f main.o binary_search.o