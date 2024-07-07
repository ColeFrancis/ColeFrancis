Chip8: main.o io.o init.o
	gcc -o Chip8 main.o io.o init.o

main.o: main.c io.h init.h
	gcc -c main.c

io.o: io.c io.h
	gcc -c io.c

init.o: init.c init.h
	gcc -c init.c
