clox: main.o
	gcc -o $@ $<
main.o: main.c
