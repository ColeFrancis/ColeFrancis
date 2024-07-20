#include <SDL2/SDL.h>
#include <stdio.h>

#include "io.h"

int init_renderer(SDL_Window **window, SDL_Renderer **renderer, unsigned int width, unsigned int height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		fprintf(stderr, "Error: SDL couldn't initialize. %s\n", SDL_GetError());
		return 1;
	}

	*window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width * WINDOW_SCALE, height * WINDOW_SCALE, SDL_WINDOW_SHOWN);
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

void refresh_screen(SDL_Renderer *renderer, unsigned char *disp, unsigned int width, unsigned int height)
{
	int i, j;
	unsigned char* p = disp;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (i = 0; i < height * WINDOW_SCALE; i += WINDOW_SCALE)
	{
		for (j = 0; j < width * WINDOW_SCALE; j += WINDOW_SCALE)
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

void update_keys (SDL_KeyboardEvent *key, unsigned char *key_buffer, unsigned char state)
{
	switch(key->keysym.scancode)
	{
		case SDL_SCANCODE_1:
			key_buffer[1] = state;
			break;

		case SDL_SCANCODE_2:
			key_buffer[2] = state;
			break;
			
		case SDL_SCANCODE_3:
			key_buffer[3] = state;
			break;
			
		case SDL_SCANCODE_4:
			key_buffer[0xC] = state;
			break;
			
		case SDL_SCANCODE_Q:
			key_buffer[4] = state;
			break;
			
		case SDL_SCANCODE_W:
			key_buffer[5] = state;
			break;
			
		case SDL_SCANCODE_E:
			key_buffer[6] = state;
			break;
			
		case SDL_SCANCODE_R:
			key_buffer[0xD] = state;
			break;
			
		case SDL_SCANCODE_A:
			key_buffer[7] = state;
			break;
			
		case SDL_SCANCODE_S:
			key_buffer[8] = state;
			break;
			
		case SDL_SCANCODE_D:
			key_buffer[9] = state;
			break;
			
		case SDL_SCANCODE_F:
			key_buffer[0xE] = state;
			break;
			
		case SDL_SCANCODE_Z:
			key_buffer[0xA] = state;
			break;
			
		case SDL_SCANCODE_X:
			key_buffer[0] = state;
			break;
			
		case SDL_SCANCODE_C:
			key_buffer[0xB] = state;
			break;
			
		case SDL_SCANCODE_V:
			key_buffer[0xF] = state;
			break;
	}
}
