#include <stdlib.h>
#include <stdio.h>

#include "init.h"

/*
 * Function: initialize
 *
 * Summary: initalizes the values of a chip8
 *
 */

void init_chip (Chip8_t *chip8)
{
	unsigned char *p;
	
	chip8->pc = PROG_START;
	
	chip8->sp = 0;
	
	chip8->delay = 0;
	chip8->sound = 0;
	
	for (p = chip8->v; p < chip8->v + 16; p++)
	{
		*p = 0;
	}
	
	load_fonts(chip8->mem + FONT_START);

	chip8->refresh_disp = 0;
}

void load_fonts(unsigned char *mem_start)
{
	// 0
	mem_start[0] = 0xF0;
	mem_start[1] = 0x90;
	mem_start[2] = 0x90;
	mem_start[3] = 0x90;
	mem_start[4] = 0xF0;
	
	// 1
	mem_start[5] = 0x20;
	mem_start[6] = 0x60;
	mem_start[7] = 0x20;
	mem_start[8] = 0x20;
	mem_start[9] = 0x70;
	
	// 2
	mem_start[10] = 0xF0;
	mem_start[11] = 0x10;
	mem_start[12] = 0xF0;
	mem_start[13] = 0x80;
	mem_start[14] = 0xF0;
	
	// 3
	mem_start[15] = 0xF0;
	mem_start[16] = 0x10;
	mem_start[17] = 0xF0;
	mem_start[18] = 0x10;
	mem_start[19] = 0xF0;
	
	// 4
	mem_start[20] = 0x90;
	mem_start[21] = 0x90;
	mem_start[22] = 0xF0;
	mem_start[23] = 0x10;
	mem_start[24] = 0x10;
	
	// 5
	mem_start[25] = 0xF0;
	mem_start[26] = 0x80;
	mem_start[27] = 0xF0;
	mem_start[28] = 0x10;
	mem_start[29] = 0xF0;
	
	// 6
	mem_start[30] = 0xF0;
	mem_start[31] = 0x80;
	mem_start[32] = 0xF0;
	mem_start[33] = 0x90;
	mem_start[34] = 0xF0;
	
	// 7
	mem_start[35] = 0xF0;
	mem_start[36] = 0x10;
	mem_start[37] = 0x20;
	mem_start[38] = 0x40;
	mem_start[39] = 0x40;
	
	// 8
	mem_start[40] = 0xF0;
	mem_start[41] = 0x90;
	mem_start[42] = 0xF0;
	mem_start[43] = 0x90;
	mem_start[44] = 0xF0;
	
	// 9
	mem_start[45] = 0xF0;
	mem_start[46] = 0x90;
	mem_start[47] = 0xF0;
	mem_start[48] = 0x10;
	mem_start[49] = 0xF0;
	
	// A
	mem_start[50] = 0xF0;
	mem_start[51] = 0x90;
	mem_start[52] = 0xF0;
	mem_start[53] = 0x90;
	mem_start[54] = 0x90;
	
	// B
	mem_start[55] = 0xE0;
	mem_start[56] = 0x90;
	mem_start[57] = 0xE0;
	mem_start[58] = 0x90;
	mem_start[59] = 0xE0;
	
	// C
	mem_start[60] = 0xF0;
	mem_start[61] = 0x80;
	mem_start[62] = 0x80;
	mem_start[63] = 0x80;
	mem_start[64] = 0xF0;
	
	// D
	mem_start[65] = 0xE0;
	mem_start[66] = 0x90;
	mem_start[67] = 0x90;
	mem_start[68] = 0x90;
	mem_start[69] = 0xE0;
	
	// E
	mem_start[70] = 0xF0;
	mem_start[71] = 0x80;
	mem_start[72] = 0xF0;
	mem_start[73] = 0x80;
	mem_start[74] = 0xF0;
	
	// F
	mem_start[75] = 0xF0;
	mem_start[76] = 0x80;
	mem_start[77] = 0xF0;
	mem_start[78] = 0x80;
	mem_start[79] = 0x80;
}

/*
 * Function: load_rom
 *
 * Summary: loads the contents of a binary file into the chip8's ram
 *
 * Pseudocode:
 *              
 * Begin
 *      Open file
 *      Get size of file
 *      Load file into memory array
 *      Close file
 * End
 */

void load_rom (char *file_name, unsigned char *mem_start, int load_max_size)
{
        FILE *file;
        long file_size;
        size_t read_result;
        int read_size;

        file = fopen(file_name, "rb");
        if (file == NULL)
        {
                fprintf(stderr, "Error, unable to open %s\n", file_name);
                exit(1);
        }

        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        rewind(file);

        read_size = (file_size > (long)load_max_size) ? load_max_size : (int) file_size;

        read_result = fread(mem_start, 1, read_size, file);
        if (read_result != read_size)
        {
                fprintf(stderr, "Error in loading memory");
                exit(1);
        }

        fclose(file);
}

