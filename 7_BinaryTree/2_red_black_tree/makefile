main: main.o red_black.o rotate.o
	gcc -Wall -o main main.o red_black.o rotate.o

main.o: main.c
	gcc -Wall -c main.c
main.o: red_black.h rotate.h tree_struct.h

red_black.o: red_black.c
	gcc -Wall -c red_black.c
red_black.o: tree_struct.h rotate.h

rotate.o: rotate.c
	gcc -Wall -c rotate.c
rotate.o: tree_struct.h


.PHONY: clean
clean:
	rm -f main main.o red_black.o rotate.o
