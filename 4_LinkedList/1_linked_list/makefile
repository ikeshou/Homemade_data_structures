main: main.o linked.o
	gcc -Wall -o main main.o linked.o
main.o: main.c
	gcc -Wall -c main.c
main.o: linked.h
linked.o: linked.c
	gcc -Wall -c linked.c

.PHONY: clean
clean:
	rm -f main main.o linked.o