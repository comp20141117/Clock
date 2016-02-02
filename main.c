#include "global.h"
#include "model.h"
#include "view.h"
#include "controller.h"
#include <stdio.h>

int init();
int load_media();
void quit();

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;

int init()
{
	int success = 1;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = 0;
	}
	else {
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!\n");
		}

		g_window = SDL_CreateWindow(
			"SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if(g_window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = 0;
		}
		else {
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(g_renderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
		}
	}

	return success;
}

int load_media()
{
	int success = 1;

	success = view_load_media();

	return success;
}

void quit()
{
	view_free_media();

	SDL_DestroyRenderer(g_renderer);
	g_renderer = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	SDL_Quit();
}

void title_debug()
{
	char buf[256];
	sprintf(
		buf, "%d/%d %02d:%02d:%02d %c%c",
		month, day, hour, minute, second,
		key_a ? 'A' : ' ',
		key_b ? 'B' : ' ');
	SDL_SetWindowTitle(g_window, buf);
}

int main(int argc, char *argv[])
{
	if(!init()) {
		printf("Failed to initialize!");
	}
	else {
		if(!load_media()) {
			printf("Failed to load media!");
		}
		else {
			int quit = 0;
			SDL_Event e;

			Uint32 base_time = SDL_GetTicks();
			const Uint8 *keyStates = SDL_GetKeyboardState(NULL);

			view_paint();

			while(!quit) {
				SDL_PumpEvents();
				key_a = keyStates[SDL_SCANCODE_LEFTBRACKET];
				key_b = keyStates[SDL_SCANCODE_RIGHTBRACKET];

				while(SDL_PollEvent(&e) != 0) {
					if(e.type == SDL_QUIT) {
						quit = 1;
					}
				}

				Uint32 cur_time = SDL_GetTicks();
				Uint32 delta_time = cur_time - base_time;
				if(delta_time > 50) {
					unsigned n = delta_time / 50;
					while(n--) {
						base_time += 50;
						timer_int();
					}
					view_paint();
					title_debug();
				}
			}
		}
	}

	quit();

	return 0;
}
