all:
	gcc -c -Wall main.c ./lib/manage_bin/manage_bin.c ./lib/manage_csv/manage_csv.c ./lib/binarioNaTela/binarioNaTela.c ./lib/funcionalidades/funcionalidades.c
	gcc -Wall main.o manage_bin.o manage_csv.o binarioNaTela.o funcionalidades.o -o ./main

run:
	./main
