#include <SDL2/SDL.h>
#include <stdio.h>

#include "init.h"
#include "io.h"

void init_renderer(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Error: SDL couldn't initialize. %s\n", SDL_GetError());
		return 1;
	}

	*window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * WINDOW_SCALE, SCREEN_HEIGHT * WINDOW_SCALE, SDL_WINDOW_SHOWN);
	if (*window == NULL)
	{
		fprintf(stderr, "Error: Window couldn't be created %s\n", SDL_GetError());
		return 1;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
		fprintf(stderr, "Error: Renderer couldn't be created. %s\n", SDL_GetError());
		return 1;
	}
}

void refresh_screen(SDL_Renderer *renderer, unsigned char *disp)
{
	int i, j;
	unsigned char* p = disp;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (i = 0; i < SCREEN_HEIGHT * WINDOW_SCALE; i += WINDOW_SCALE)
	{
		for (j = 0; j < SCREEN_WIDTH * WINDOW_SCALE; j += WINDOW_SCALE)
		{
			if (*p)
			{
				SDL_Rect rect;
				rect.x = j;
				rect.y = i;
				rect.w = WINDOW_SCALE;
				rect.h = WINDOW_SCALE;

				SDL_RenderFillRect(renderer, &rect);
			}
			
			p++;
		}
	}

	SDL_RenderPresent(renderer);
}

void refresh_screen_terminal(unsigned char* disp, unsigned int width, unsigned int height)
{
	int i, j;
	unsigned char* p = disp;
	
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
