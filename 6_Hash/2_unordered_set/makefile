main: main.o set.o hash_func.o doubly.o
	gcc -Wall -o main main.o set.o hash_func.o doubly.o

main.o: main.c
	gcc -Wall -c main.c
main.o: hash_func.h doubly.h struct_for_set.h

set.o: set.c
	gcc -Wall -c set.c
set.o: hash_func.h doubly.h struct_for_set.h

# math.h を使う
hash_func.o: hash_func.c
	gcc -Wall -lm -c hash_func.c

doubly.o: doubly.c
	gcc -Wall -c doubly.c
doubly.o: struct_for_set.h


.PHONY: clean
clean:
	rm -f main main.o set.o hash_func.o doubly.o