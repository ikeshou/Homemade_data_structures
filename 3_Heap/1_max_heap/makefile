main: main.o heap.o
	gcc -Wall -o main main.o heap.o
main.o: main.c
	gcc -Wall -c main.c
main.o: heap.h
heap.o: heap.c
	gcc -Wall -c heap.c

.PHONY: clean
clean:
	rm -f main main.o heap.o
