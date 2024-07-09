#include <stdlib.h>
#include <stdio.h>

#include "init.h"
#include "io.h"

void run_cycle (Chip8_t *chip8);

/*
 * Function: main
 *
 * Summary: Creates an instance of chip8, initializes it, then runs all the instructions
 *
 */

int main (int argc, char **argv)
{
	Chip8_t *chip8 = (Chip8_t *) malloc(sizeof(Chip8_t));

	initialize(chip8);

	load_rom(argv[1], chip8->mem, 4096);
	
	
	for (int temp=0;temp<100;temp++)
	{
		run_cycle(chip8);
	}	

	return 1;
}

void run_cycle (Chip8_t *chip8)
{
	chip8->ir = (chip8->mem[chip8->pc] << 8) | chip8->mem[chip8->pc+1];
	chip8->pc += 2;

	printf("%X\n", chip8->ir);
	/*
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
	*/
}