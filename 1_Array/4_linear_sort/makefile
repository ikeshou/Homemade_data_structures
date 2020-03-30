main: main.o stable_counting.o
	gcc -Wall -O0 -o main -g main.o stable_counting.o
main.o: main.c
	gcc -Wall -O0 -c -g main.c
main.o: stable_counting.h
stable_counting.o: stable_counting.c
	gcc -Wall -O0 -c -g stable_counting.c

.PHONY: clean
clean:
	rm -f main main.o stable_counting.o
