main: main.o inversion.o nth_smallest.o
	gcc -Wall -o main main.o inversion.o nth_smallest.o
main.o: main.c
	gcc -Wall -c main.c
main.o: nth_smallest.h
main.o: inversion.h
inversion.o: inversion.c
	gcc -Wall -c inversion.c
nth_smallest.o: nth_smallest.c
	gcc -Wall -c nth_smallest.c

.PHONY: clean
clean:
	rm -f main main.o inversion.o