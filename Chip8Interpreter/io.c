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
 *	Loop through each row of the screen
 *		Loop screen width / 8 times
 *			Loop through each bit of byte pointed to by display buffer
 *				Print XX or space
 *			End loop
 *
 *			Increment display buffer pointer
 *		End loop
 *		Print new line
 *	End loop
 * End
 */

void refresh_screen(unsigned char* disp)
{
	int i, j, k;
	unsigned char c;
        unsigned char *p;

        //system("clear"); // system("cls"); for windows. Find out how to let it change

        p = disp;
        for (i = 0; i < SCREEN_HEIGHT; i++)
        {
                for (j = 0; j < SCREEN_WIDTH / 8; j++)
		{
			c = *p;

			for (k = 0; k < 8; k++)
			{
				if ((c & 0xF0) == 0xF0)
				{
					printf("XX");
				}
				else
				{
				printf("  ");
				}
				c << 1;	
			}

			p++;
		}
	}
}
