main: main.o circular.o
	gcc -Wall -o main main.o circular.o
mai.o: main.c
	gcc -Wall -c main.c
main.o: circular.h
circular.o: circular.c
	gcc -Wall -c circular.c

.PHONY: clean
clean:
	rm -f main main.o circular.o