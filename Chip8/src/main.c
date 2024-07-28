#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "init.h"
#include "io.h"

// Debugging and testing options
#undef PRINT_REGS
#undef BREAKPOINTS

void run_cycle (Chip8_t *chip8);
void delay (unsigned int milliseconds);
void stack_push(unsigned short *stack, unsigned short *sp, unsigned short addr);
unsigned short stack_pop(unsigned short *stack, unsigned short *sp);

int main (int argc, char **argv)
{
	int quit = 0;

	Chip8_t *chip8 = (Chip8_t *) malloc(sizeof(Chip8_t));
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event e;

	if (argc < 2)
	{
		fprintf(stderr, "Error: no program (ch8) file included\n");
		return 1;
	}

	init_chip(chip8);
	load_rom(argv[1], chip8->mem + PROG_START, 4096 - PROG_START);
	
	init_renderer(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	while (!quit)
	{
		// Check for program exit and keystrokes
		while (SDL_PollEvent(&e) != 0)
		{
			switch( e.type)
			{
				case SDL_QUIT:
					quit = 1;
					break;
				
				case SDL_KEYDOWN:
					update_keys (&e.key, chip8->key, 1);
					break;

				case SDL_KEYUP:
					update_keys (&e.key, chip8->key, 0);
					break;
			}
		}

		run_cycle(chip8);

		if (chip8->refresh_disp)
		{
			refresh_screen(renderer, chip8->disp, SCREEN_WIDTH, SCREEN_HEIGHT);
			chip8->refresh_disp = 0;
		}
		
		#ifdef BREAKPOINTS
			getchar();
		#else
			delay(16);
		#endif
	}	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}

void run_cycle (Chip8_t *chip8)
{
	unsigned short inst;
	
	unsigned char vx, vy, n;
	
	int i;
	
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
			else if (inst == 0x00EE)
			{
				// 00EE: pull address off stack and jump to it
				chip8->pc = stack_pop(chip8->stack, &(chip8->sp));
			}
		    break;
		
		case 0x1000:
			// 1NNN: pc = NNN
			chip8->pc = inst & 0x0FFF;
		    break;

		case 0x2000:
			// 2NNN: push current address to stack, then jump to NNN
			stack_push(chip8->stack, &(chip8->sp), chip8->pc);
			
			chip8->pc = inst & 0x0FFF;
		    break;
		      
		case 0x3000:
			// 3XNN: Skip one instruction if VX is equal to NN
			if (chip8->v[(unsigned char) (inst >> 8) & 0x0F] == (unsigned char) inst)
			{
				chip8->pc += 2;
			}
		    break;

		case 0x4000:
			// 4XNN: Skip one instruction if VX is NOT equal to NN
			if (chip8->v[(unsigned char) (inst >> 8) & 0x0F] != (unsigned char) inst)
			{
				chip8->pc += 2;
			}
		    break;

		case 0x5000:
			// 5XY0: skip next instrucion if VX and VY are equal
			if (chip8->v[(unsigned char) (inst >> 8) & 0x0F] == chip8->v[(unsigned char) (inst >> 4) & 0x0F])
			{
				chip8->pc += 2;
			}
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
			vx = chip8->v[(unsigned char) (inst >> 8) & 0x0F];
			vy = chip8->v[(unsigned char) (inst >> 4) & 0x0F];
			
			switch (inst & 0x000F)
			{
				case 0x0000:
					// 8XY0: VX is set to vy
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = vy;
					break;
					
				case 0x0001:
					// 8XY1: VX = VX | VY
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = vx | vy;
					break;
					
				case 0x0002:
					// 8XY2: VX = VX & VY
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = vx & vy;
					break;
					
				case 0x0003:
					// 8XY3: VX = VX ^ VY
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = vx ^ vy;
					break;
					
				case 0x0004:
					// 8XY4: VX = VX + VY
					//		 If result is larger than 255, VF set to 1. If not, set to 0
					unsigned short sum;
					
					chip8->v[0xF] = 0;
					
					sum = (unsigned short) vx + (unsigned short) vy;
					
					if (sum > 255)
					{
						chip8->v[0xF] = 1;
					}
					
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = sum;
					break;
					
				case 0x0005:
					// 8XY5: VX = VX - VY
					//		 If result is positive, VF set to 1. If not, set to 0
					unsigned short diff;
					
					chip8->v[0xF] = 1;
					
					sum = (unsigned short) vx - (unsigned short) vy;
					
					if (sum > 255)
					{
						chip8->v[0xF] = 0;
					}
					
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = sum;
					
					break;
					
				case 0x0006:
					// 8XY6: VX >> 1
					chip8->v[0xF] = vx & 1;
					
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = vx >> 1;
					break;
					
				case 0x0007:
					// 8XY7: VX = VY - VX
					//		 If result is positive, VF set to 1. If not, set to 0
					
					chip8->v[0xF] = 1;
					
					sum = (unsigned short) vy - vx;
					
					if (sum > 255)
					{
						chip8->v[0xF] = 0;
					}
					
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = sum;
					break;
					
				case 0x000E:	
					// 8XYE: VX << 1
					chip8->v[0xF] = (vx >> 7) & 1;
					
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = vx << 1;
					break;
			}
		    break;

		case 0x9000:
			// 5XY0: skip next instrucion if VX and VY NOT are equal
			if (chip8->v[(unsigned char) (inst >> 8) & 0x0F] != chip8->v[(unsigned char) (inst >> 4) & 0x0F])
			{
				chip8->pc += 2;
			}
		    break;
	
		case 0xA000:
			// ANNN: index = NNN
			chip8->index = inst & 0x0FFF;
		    break;

		case 0xB000:
			// BXNN: Jump to address XNN + value in VX
			chip8->pc = (inst & 0x0FFF) +  chip8->v[(unsigned char) (inst >> 8) & 0x0F];
		    break;

		case 0xC000:
			// CXNN: Generate random number, ands it with NN and stores in VX
			srand(time(NULL));
			
			unsigned char rand_val = (unsigned char) rand() % 256;
			
			chip8->v[(unsigned char) (inst >> 8) & 0x0F] = rand_val & (unsigned char) inst;
		    break;
		
		case 0xD000:
			// DXYN: Draw N pixel tall sprite from mem location ir at horizontal x coordinate in VX and y coordinate in VY. 
			// 		 All pixel on in the spirte flip the pixels on the screen
			unsigned char x;
			unsigned char y;
			unsigned char n;
			
			unsigned char *spd;
			
			unsigned char temp_x;
			int bit;
			
			chip8->v[0xF] = 0;
			
			x = chip8->v[(inst >> 8) & 0x0F];
			x %= SCREEN_WIDTH;
			
			y = chip8->v[(inst >> 4) & 0x0F];
			y %= SCREEN_HEIGHT;
			
			n = (unsigned char) inst & 0x0F;
			
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

			chip8->refresh_disp = 1;

		    break;

		case 0xE000:
			vx = chip8->v[(unsigned char) (inst >> 8) & 0x0F];
				
			switch (inst & 0x00FF)
			{
				case 0x009E:
					// EX9E: skip one instruction if key corresponding to value in vx is pressed
					if (chip8->key[vx & 0xF])
					{
						chip8->pc += 2;
					}
					break;
					
				case 0x00A1:	
					// EXA1: skip one instruction if key corresponding to value in vx NOT is pressed
					if (!chip8->key[vx & 0xF])
					{
						chip8->pc += 2;
					}
					break;
			}
		    break;

		case 0xF000:
			switch (inst & 0x00FF)
			{
				case 0x0007:
					// FX07: Set vx to current value in delay timer
					
					chip8->v[(unsigned char) (inst >> 8) & 0x0F] = chip8->delay;
					break;
					
				case 0x0015:
					// FX15: set delay timer to value in vx
					
					chip8->delay = chip8->v[(unsigned char) (inst >> 8) & 0x0F];
					break;
					
				case 0x0018:
					// FX18: Set sound timer to the value in vx
					
					chip8->sound = chip8->v[(unsigned char) (inst >> 8) & 0x0F];
					break;
					
				case 0x001E:
					// FX1E: index += VX, VF = 1 if i overflows ffrom 0FFF to or above 1000
					
					chip8->index += chip8->v[(unsigned char) (inst >> 8) & 0x0F];
					
					if (chip8->index >= 0x1000)
					{
						chip8->v[0xF] = 1;
					}
					break;
					
				case 0x000A:
					//FX0A: stops executing instructions and wait for input.
					//	 	if a key is pressed, its hex value is put in vx
					unsigned char key_pressed = 0;
					
					for (int i = 0; i <= 0xF; i++)
					{
						if (chip8->key[i])
						{
							chip8->v[(unsigned char) (inst >> 8) & 0x0F] = i;
							
							key_pressed = 1;
							break;
						}
					}
					
					if (key_pressed)
					{
						chip8->pc -= 2;
					}
					
					break;
					
				case 0x0029:
					// FX29: index = address of last hex character stored in vx
					vx = chip8->v[(unsigned char) (inst >> 8) & 0x0F] & 0x0F;
					
					chip8->index = FONT_START;
					while (vx > 0)
					{
						chip8->index += 5;
						vx--;
					}
					
					break;
					
				case 0x0033:
					// FX33: First binary digit of vx stored in index, second in index + 1, and third in index + 2
					
					vx = chip8->v[(unsigned char) (inst >> 8) & 0x0F];
					
					chip8->mem[chip8->index] = (vx / 100) % 10;
					chip8->mem[chip8->index + 1] = (vx / 10) % 10;
					chip8->mem[chip8->index + 3] = vx % 10;
					break;
					
				case 0x0055:
					// FX55: v0..vx = mem[index]..me[index + x]
					
					n = (unsigned char) (inst >> 8) & 0x0F;
					
					for (i = 0; i <= n; i++)
					{
						chip8->v[i] = chip8->mem[chip8->index + i];
					}
					break;
					
				case 0x0065:
					// FX65: mem[index]..me[index + x] = v0..vx
					
					n = (unsigned char) (inst >> 8) & 0x0F;
					
					for (i = 0; i <= n; i++)
					{
						chip8->mem[chip8->index + i] = chip8->v[i];
					}
					break;
			}
		    break;
	}

	chip8->delay--;
	chip8->sound--;
	
	#ifdef PRINT_REGS
		printf("inst: 0x%X\n", inst);
		printf("pc: 0x%X\n", chip8->pc);
		printf("index: 0x%X\n", chip8->index);
		
		for (i = 0; i <= 0xF; i++)
			printf("v[%X]: 0x%X\n", i, chip8->v[i]);
		
		printf("\n");
		
		printf("SP: 0x%X\n", chip8->sp);
		for (int j = 0; j < chip8->sp; j++)
		{
			printf("stack[%X]: 0x%X\n", j, chip8->stack[j]);
		}
		
		printf("\n");
	#endif
}

void delay (unsigned int milliseconds)
{
	clock_t start = clock();
	
	while (clock() < start + milliseconds)
		;
}

void stack_push(unsigned short *stack, unsigned short *sp, unsigned short addr)
{
	if (*sp < 15)
	{
		stack[*sp] = addr;
		
		(*sp)++;
	}
	else
	{
		fprintf(stderr, "Error: stack overflow");
		exit(1);
	}
}

unsigned short stack_pop(unsigned short *stack, unsigned short *sp)
{
	if (*sp > 0)
	{
		return stack[--(*sp)];
	}
	else
	{
		fprintf(stderr, "Error: stack underflow");
		exit(1);
	}
}