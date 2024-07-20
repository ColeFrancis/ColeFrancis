#ifndef INIT_H
#define INIT_H

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

#define PROG_START 0x200
#define FONT_START 0x050

typedef struct {
	unsigned char v[16];

	//unsigned short ir;
	unsigned short pc;
	
	unsigned short index;

	unsigned char delay;
	unsigned char sound;

	unsigned short stack[16];
	unsigned short sp;

	unsigned char mem[4096];

	unsigned char key[16];

	unsigned char disp [SCREEN_WIDTH * SCREEN_HEIGHT];
	unsigned char refresh_disp;
} Chip8_t;

void init_chip (Chip8_t *chip8);
void load_fonts(unsigned char *mem_start);
void load_rom (char *file_name, unsigned char *mem_start, int load_max_size);

#endif
