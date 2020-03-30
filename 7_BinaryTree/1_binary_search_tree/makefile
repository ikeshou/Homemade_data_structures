main: main.o tree.o rotate.o
	gcc -Wall -o main main.o tree.o rotate.o
main.o: main.c
	gcc -Wall -c main.c
main.o: tree.h rotate.h
tree.o: tree.c
	gcc -Wall -c tree.c
rotate.o: rotate.c
	gcc -Wall -c rotate.c
rotate.o: tree.h


.PHONY: clean
clean:
	rm -f main main.o tree.o rotate.o
