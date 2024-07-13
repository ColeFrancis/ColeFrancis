#include <stdio.h>
#include <stdlib.h>

#include "io.h"

/* 
 * Function: refresh_screen
 *
 * Summary: When called, reads the contents of the display buffer and rerenders the screen, byte by byte (or bit by bit)
 */

void refresh_screen(unsigned char* disp, unsigned int int_size, unsigned int width, unsigned int height)
{
    system("clear"); // system("cls"); for windows. Find out how to let it change
	
	int i, j;
	unsigned char* p;
	
	// Use this if the screen buffer stores a pixels state per bit not per byte
	/*
	for (i = 1, p = disp; p < disp + (width * height / 8); i++, p++)
	{
		for (int j = 7; j >= 0; j--)
		{
			if (((*p) >> j) & 1)
			{
				printf("XX");
			}
			else
			{
				printf("  ");
			}
		}
		
		if (i == (width / int_size))
		{
			printf("\n");
			i = 0;
		}
	}
	*/
	p = disp;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
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

/* 
 * Function: register_keys
 *
 * Summary: saves the state of each of the 16 keys (1 if pressed, 0 if not) into the keys array
 */

void register_keys(unsigned char *keys)
{
	
}
