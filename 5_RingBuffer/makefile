main: main.o deque.o
	gcc -Wall -o main main.o deque.o
main.o: main.c
	gcc -Wall -c main.c
main.o: deque.h	
deque.o: deque.c
	gcc -Wall -c deque.c

.PHONY: clean
clean:
	rm -f main main.o deque.o
