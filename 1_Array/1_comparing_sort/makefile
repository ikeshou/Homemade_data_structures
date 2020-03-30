main: main.o sort.o
	gcc -Wall -o main main.o sort.o
main.o: main.c
	gcc -Wall -c main.c
main.o: sort.h
sort.o: sort.c
	gcc -Wall -c sort.c

# ターゲット名がファイルでないものをPHONYと呼ぶのだった。cleanというファイルがあってもうまく下記コマンドを実行するためのもの
.PHONY: clean
clean:
	rm -f main main.o sort.o