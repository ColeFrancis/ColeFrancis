#include <stdlib.h>
#include <stdio.h>

#include "init.h"
#include "io.h"

/*
 * Function: main
 *
 * Summary:
 *
 * Pseudocode:
 *
 */

int main (int argc, char **argv)
{
	unsigned char disp[SCREEN_WIDTH * SCREEN_HEIGHT / 8];

	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT / 8; i++)
	{
		disp[i] = 1;
	}

	refresh_screen(disp);

	return 1;
}
