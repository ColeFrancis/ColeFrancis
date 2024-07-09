#ifndef INIT_H
#define INIT_H

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

typedef struct {
	unsigned char v[16];

	unsigned short ir;
	unsigned short pc;

	unsigned char delay;
	unsigned char sound;

	unsigned short stack[16];
	unsigned short *sp;

	unsigned char mem[4096];

	unsigned char key[16];

	unsigned char disp [SCREEN_WIDTH * SCREEN_HEIGHT / 8];
} Chip8_t;

void initialize (Chip8_t *chip8);

void load_rom (char *file_name, unsigned char *mem_start, int load_max_size);

#endif
