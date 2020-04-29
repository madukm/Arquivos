all:
	gcc -c main.c ./lib/manage_bin/manage_bin.c ./lib/manage_csv/manage_csv.c
	gcc main.o manage_bin.o -o ./main

run:
	./main