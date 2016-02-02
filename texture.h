#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include <SDL2/SDL.h>

typedef struct _LTexture
{
	SDL_Texture *texture;
	int width, height;
} LTexture;

void texture_init(LTexture *me);
void texture_free(LTexture *me);
int texture_load(LTexture *me, const char *path);
void texture_render(LTexture *me, int x, int y, SDL_Rect *clip);

#endif

