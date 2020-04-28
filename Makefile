all:
	gcc -c -Wall main.c ./lib/manage_bin/manage_bin.c ./lib/manage_csv/manage_csv.c
	gcc -Wall main.o manage_bin.o -o ./main

run:
	./main