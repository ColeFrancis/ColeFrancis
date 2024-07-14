CC = gcc

COMPILER_FLAGS = -w $(shell sdl2-config --cflags)

LINKER_FLAGS =  $(shell sdl2-config --libs)

SRC_FILES = main.c io.c init.c

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_NAME = Chip8

all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: main.c io.h init.h
	$(CC) $(COMPILER_FLAGS) -c main.c -o main.o
	gcc -c main.c

io.o: io.c io.h
	$(CC) $(COMPILER_FLAGS) -c io.c -o io.o

init.o: init.c init.h
	$(CC) $(COMPILER_FLAGS) -c init.c -o init.o

clean:
	rm -f $(OBJ_FILES) $(OBJ_NAME)