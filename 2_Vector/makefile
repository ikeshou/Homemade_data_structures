main: main.o elastic_array.o
	gcc -Wall -o main main.o elastic_array.o
main.o: main.c
	gcc -Wall -c main.c
main.o: elastic_array.h
elastic_array.o: elastic_array.c
	gcc -Wall -c elastic_array.c

.PHONY: clean
clean:
	rm -f main main.o elastic_array.o