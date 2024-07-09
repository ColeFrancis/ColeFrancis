#include <stdlib.h>
#include <stdio.h>

#include "init.h"

/*
 * Function: initialize
 *
 * Summary: initalizes the values of a chip8
 *
 */

void initialize (Chip8_t *chip8)
{
	
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

