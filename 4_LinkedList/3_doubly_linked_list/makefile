main: main.o doubly.o
	gcc -Wall -o main main.o doubly.o
main.o: main.c
	gcc -Wall -c main.c
main.o: doubly.h	
doubly.o: doubly.c
	gcc -Wall -c doubly.c

.PHONY: clean
clean:
	rm -f main main.o doubly.o