main: main.o max_pqueue.o
	gcc -Wall -o main main.o max_pqueue.o
main.o: main.c
	gcc -Wall -c main.c
main.o: max_pqueue.h
max_pqueue.o: max_pqueue.c
	gcc -Wall -c max_pqueue.c

.PHONY: clean
clean:
	rm -f main main.o max_pqueue.o