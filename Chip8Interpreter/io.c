#include <stdio.h>
#include <stdlib.h>

#include "io.h"

/* File for all functions relating to getting keys and writing to the screen
 *
 * ex: 
 * 	refresh screen (reads through screen buffer and draws to screen)
 * 	save keys (saves the current states of the keys, maybe into a series of registers
 */

/* 
 * Function: refresh_screen
 *
 * Summary: When called, reads the contents of the display buffer and rerenders the screen
 *
 * Pseudocode:
 *
 * Begin
 * 	Clear the current screen
 *
 *	Loop through disp array
 *		Loop through each bit of current int
 *			print state to pixel
 *		End loop
 *		If then
 *			Print newline every (width / int_size) time
 *		End if
 *	End loop
 * End
 */

void refresh_screen(unsigned char* disp, unsigned int int_size, unsigned int width, unsigned int height)
{
    //system("clear"); // system("cls"); for windows. Find out how to let it change
	
	int i, j;
	unsigned char* p;
	
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
}
