#ifndef IO_H
#define IO_H

#define WINDOW_SCALE 15

int init_renderer(SDL_Window **window, SDL_Renderer **renderer, unsigned int width, unsigned int height);
void refresh_screen(SDL_Renderer *renderer, unsigned char *disp, unsigned int width, unsigned int height);
void update_keys (SDL_KeyboardEvent *key, unsigned char *key_buffer, unsigned char state);

#endif
