main: main.o hash_table.o hash_func.o doublyLL_record.o
	gcc -Wall -o main main.o hash_table.o hash_func.o doublyLL_record.o

main.o: main.c
	gcc -Wall -c main.c
main.o: hash_func.h doublyLL_record.h struct_for_hash.h

hash_table.o: hash_table.c
	gcc -Wall -c hash_table.c
hash_table.o: hash_func.h doublyLL_record.h struct_for_hash.h

# math.h を使う
hash_func.o: hash_func.c
	gcc -Wall -lm -c hash_func.c
doublyLL_record.o: doublyLL_record.c
	gcc -Wall -c doublyLL_record.c

# test for hash_func.c
check_hash_func: check_hash_func.o hash_func.o
	gcc -Wall -o check_hash_func check_hash_func.o hash_func.o
check_hash_func.o: check_hash_func.c
	gcc -Wall -c check_hash_func.c
check_hash_func.o: hash_func.h

# test for doublyLL_record.c
check_doublyLL_record: check_doublyLL_record.o doublyLL_record.o
	gcc -Wall -o check_doublyLL_record check_doublyLL_record.o doublyLL_record.o
check_doublyLL_record.o: check_doublyLL_record.c
	gcc -Wall -c check_doublyLL_record.c
check_doublyLL_record.o: doublyLL_record.h struct_for_hash.h


.PHONY: clean
clean:
	rm -f main check_hash_func check_doublyLL_record main.o hash_table.o hash_func.o doublyLL_record.o check_hash_func.o check_doublyLL_record.o