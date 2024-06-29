#include <stdio.h>
#include <stdlib.h>

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

	unsigned char disp [SCREEN_WIDTH * SCREEN_HEIGHT];
} Chip8_t;

void run_cycle (Chip8_t *chip8);
void initialize (Chip8_t *chip8);
void load_rom (char *name, unsigned char *mem_start);
void refresh_screen(unsigned char* disp);

int main (int argc, char **argv)
{
	Chip8_t *chip8 = (Chip8_t *) malloc(sizeof(Chip8_t));

	initialize(chip8);

	load_rom(argv[1], chip8->mem);

	int temp;
        for (temp=0;temp<100;temp++)
        {
		// run cycle
		//
                // draw graphics if flag set
                //
                // store key pressed state
                //
                // delay

		run_cycle(chip8);
	}	

	return 1;
}

/* 
 * Function: run_cycle
 *
 * Summary: runs through one fetch, decode, execute cycle of the chip8
 *
 * Pseudocode:
 *
 * Begin
 * 	Load instruction at pc into ir
 *
 * 	switch on ir
 * 		0 instruction:
 * 		1 instruction:
 * 		2 instruction:
 * 		3 instruction:
 * 		4 instruction:
 * 		5 instruction:
 * 		6 instruction:
 * 		7 instruction:
 * 		8 instruction:
 * 		9 instruction:
 * 		A instruction:
 * 		B instruction: 
 * 		C instruction:
 * 		D instruction:
 * 		E instruction:
 * 		F instruction:
 * 	End switch
 * End
 */

void run_cycle (Chip8_t *chip8)
{
		// fetch
                //      read 2 bytes from memory into ir
                //      increment pc by 2
                // decode
                // execute

	chip8->ir = (chip8->mem[chip8->pc] << 8) | chip8->mem[chip8->pc+1];
	chip8->pc += 2;

	//printf("%X\n", chip8->ir);

	switch (chip8->ir & 0xF000)
	{
		case 0x0000:
		      break;

		case 0x1000:
		      break;

		case 0x2000:
		      break;
		      
		case 0x3000:
		      break;

		case 0x4000:
		      break;

		case 0x5000:
		      break;

		case 0x6000:
		      break;

		case 0x7000:
		      break;

		case 0x8000:
		      break;

		case 0x9000:
		      break;

		case 0xA000:
		      break;

		case 0xB000:
		      break;

		case 0xC000:
		      break;

		case 0xD000:
		      break;

		case 0xE000:
		      break;

		case 0xF000:
		      break;
	}
}

/*
 * Function: initialize
 *
 * Summary: initalizes each member of a chip8 struct
 *
 * Pseudocode:
 * 
 * Begin
 * 	Set all values to defaults
 * End
 */

void initialize (Chip8_t *chip8)
{
	chip8->ir = 0;
	chip8->pc = 0;

	chip8->sp = chip8->stack;
}

/*
 * Function: load_rom
 *
 * Summary: loads the instructions from the binary file into the chip8's ram
 *
 * Pseudocode:
 *
 * Begin
 * 	Open binary file for reeding
 *
 * 	Get size of binary file
 *
 *	Read contents of file starting at first ram address of chip8
 * End
 */
	
void load_rom (char *name, unsigned char *mem_start)
{
	FILE *file;
	long size;
	size_t result;

	file = fopen(name, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "Error, unable to open %s\n", name);
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	result = fread(mem_start, 1, size, file);
	if (result != size)
	{
		fprintf(stderr, "Error in loading memory");
		exit(1);
	}

	fclose(file);
}

/*
 * Function: refresh_screen
 *
 * Summary: loads the contents of the screen buffer into the display
 *
 * Pseudocode:
 *	Loop through each row of screen
 *		Loop through each collum
 *			Print XX if current value in screen buffer is not 0
 *			Increment pointer to display buffer
 *		End loop
 *	End loop
 * Begin
 * End
 */

void refresh_screen(unsigned char* disp)
{
	int i, j;

	unsigned char *p;

	system("clear"); // system("cls"); for windows. Find out how to let it change

	p = disp;
	for (i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_WIDTH; j++)
		{
			if (*p)
			{
				printf("XX");
			}
			else
			{
				printf("  ");
			}

			p++;
		}
		printf("\n");
	}
}
