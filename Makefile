all:
	gcc -c main.c ./lib/manage_bin/manage_bin.c
	gcc main.o manage_bin.o -o ./main

run:
	./main