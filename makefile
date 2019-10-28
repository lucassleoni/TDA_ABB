CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: abb.c minipruebas_abb.c
	$(CC) $(CFLAGS) *.c -o abb -g 

arbol: compile
	clear
	./abb

valgrind: compile
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb