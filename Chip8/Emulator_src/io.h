#ifndef IO_H
#define IO_H

#define WINDOW_SCALE 15

void init_renderer(SDL_Window **window, SDL_Renderer **renderer);

void refresh_screen(SDL_Renderer *renderer, unsigned char *disp);
void refresh_screen_terminal(unsigned char* disp, unsigned int width, unsigned int height);

void register_keys(unsigned char *keys);

#endif
