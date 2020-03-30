main: main.o circular_doubly_linked.o
	gcc -Wall -o main main.o circular_doubly_linked.o
main.o: main.c
	gcc -Wall -c main.c
main.o: circular_doubly_linked.h
circular_doubly_linked.o: circular_doubly_linked.c
	gcc -Wall -c circular_doubly_linked.c

.PHONY: clean
clean:
	rm -f main main.o circular_doubly_linked.o