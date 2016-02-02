#include "texture.h"
#include <SDL2/SDL.h>

extern SDL_Renderer *g_renderer;

void texture_init(LTexture *me)
{
	me->texture = NULL;
	me->width = 0;
	me->height = 0;
}

void texture_free(LTexture *me)
{
	if(me->texture != NULL) {
		SDL_DestroyTexture(me->texture);
		me->texture = NULL;
		me->width = 0;
		me->height = 0;
	}
}

int texture_load(LTexture *me, const char *path)
{
	SDL_Texture *texture = NULL;

	SDL_Surface *surface = SDL_LoadBMP(path);
	if(surface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x00, 0xFF, 0xFF));

		texture = SDL_CreateTextureFromSurface(g_renderer, surface);
		if(texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else {
			me->width = surface->w;
			me->height = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	me->texture = texture;
	return me->texture != NULL;
}

void texture_render(LTexture *me, int x, int y, SDL_Rect *clip)
{
	SDL_Rect renderQuad;
	renderQuad.x = x;
	renderQuad.y = y;
	renderQuad.w = me->width;
	renderQuad.h = me->height;

	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(g_renderer, me->texture, clip, &renderQuad);
}

