#include <stdlib.h>
#include <stdio.h>

#include "init.h"
#include "io.h"

#undef DEBUG

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
	
	
	/*
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		chip8->disp[i] = 0;
	}

	chip8->disp[1] = 1;
	
	refresh_screen(chip8->disp, 8, SCREEN_WIDTH, SCREEN_HEIGHT);
	*/
	
	load_rom(argv[1], chip8->mem + PROG_START, 4096 - PROG_START);
	
	for (int temp=0; temp < 4096 - PROG_START; temp++)
	{
		run_cycle(chip8);
		
		#ifdef DEBUG
			getchar();
		#endif
		
		// get keys
		// other stuff
		//delay
	}	
	
	return 1;
}

void run_cycle (Chip8_t *chip8)
{
	unsigned short inst;
	
	inst = (chip8->mem[chip8->pc] << 8) | chip8->mem[chip8->pc+1];
	chip8->pc += 2;
	
	switch (inst & 0xF000)
	{
		case 0x0000:
			if (inst == 0x00E0)
			{		
				// 00E0: clear screen
				unsigned char *p;
				
				for (p = chip8->disp; p < chip8->disp + (SCREEN_WIDTH * SCREEN_HEIGHT); p++)
				{
					*p = 0;
				}
			}
		    break;
		
		case 0x1000:
			// 1NNN: pc = NNN
			chip8->pc = inst & 0x0FFF;
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
			// 6XNN: VX = NN
			chip8->v[(unsigned char) (inst >> 8) & 0x0F] = (unsigned char) inst;
		    break;
		
		case 0x7000:
			// 7XNN: VX += NN
			chip8->v[(unsigned char) (inst >> 8) & 0x0F] += (unsigned char) inst;
		    break;

		case 0x8000:
		    break;

		case 0x9000:
		    break;
	
		case 0xA000:
			// ANNN: ir = NNN
			chip8->index = inst & 0x0FFF;
		    break;

		case 0xB000:
		    break;

		case 0xC000:
		    break;
		
		case 0xD000:
			// DXYN: Draw N pixel tall sprite from mem location ir at horizontal x coordinate in VX and y coordinate in VY. 
			// 		 All pixel on in the spirte flip the pixels on the screen
			
			chip8->v[0xF] = 0;
			
			unsigned char x = chip8->v[(inst >> 8) & 0x0F];
			unsigned char y = chip8->v[(inst >> 4) & 0x0F];
			unsigned char n = (unsigned char) inst & 0x0F;
			
			unsigned char *spd;
			
			unsigned char temp_x;
			int bit;
			
			for (spd = chip8->mem + chip8->index; spd < chip8->mem + chip8->index + n && y < SCREEN_HEIGHT; spd++)
			{
				temp_x = x;
				
				for (bit = 7; bit >= 0 && temp_x < SCREEN_WIDTH; bit--)
				{
					if (((*spd) >> bit) & 1)
					{
						if (chip8->disp[(SCREEN_WIDTH * y) + temp_x])
						{
							chip8->v[0xF] = 1;
							
							chip8->disp[(SCREEN_WIDTH * y) + temp_x] = 0;
						}
						else
						{
							chip8->disp[(SCREEN_WIDTH * y) + temp_x] = 1;
						}
					}
					
					temp_x++;
				}
				
				y++;
			}
			
			refresh_screen(chip8->disp, 8, SCREEN_WIDTH, SCREEN_HEIGHT);
			
		    break;

		case 0xE000:
		    break;

		case 0xF000:
		    break;
	}
	
	#ifdef DEBUG
		printf("inst:%X\n", inst);
		printf("pc: %X\n", chip8->pc);
		printf("index: %X\n", chip8->index);
		
		for (int i = 0; i < 0xF; i++)
			printf("v[%d]: %X\n", i, chip8->v[i]);
		
		printf("\n");
	#endif
}