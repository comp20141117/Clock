#include "global.h"
#include "texture.h"

int digit1 = 0;
int digit2 = 0;
int colon = 1;
int digit3 = 0;
int digit4 = 0;

#define DIGIT_WIDTH 43
#define DIGIT_HEIGHT 70

#define COLON_WIDTH 25
#define COLON_HEIGHT 70

#define PANEL_WIDTH (DIGIT_WIDTH * 4 + COLON_WIDTH)
#define PANEL_HEIGHT DIGIT_HEIGHT
#define PANEL_X ((SCREEN_WIDTH - PANEL_WIDTH) / 2)
#define PANEL_Y ((SCREEN_HEIGHT - PANEL_HEIGHT) / 2)

#define COLON_X (PANEL_X + DIGIT_WIDTH * 2)
#define COLON_Y PANEL_Y

static LTexture digits_texture;

int view_load_media()
{
	int success = 1;

	texture_init(&digits_texture);

	if(!texture_load(&digits_texture, "digits.bmp")) {
		printf("Failed to load digits texture!\n");
		success = 0;
	}

	return success;
}

void view_free_media()
{
	texture_free(&digits_texture);
}

static int get_char_index(int ch)
{
	int index;

	switch(ch) {
	case 0: case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8: case 9:
		index = ch;
		break;

	case 'A':
		index = 10;
		break;

	case 'P':
		index = 11;
		break;
	
	default:
		index = 12;
		break;
	}

	return index;
}


static void render_char(int ch, int x)
{
	int char_index = get_char_index(ch);
	SDL_Rect clip = { char_index * DIGIT_WIDTH, 0, DIGIT_WIDTH, DIGIT_HEIGHT };
	texture_render(&digits_texture, PANEL_X + x, PANEL_Y, &clip);
}

static void render_colon(int show)
{
	if(show) {
		SDL_Rect clip = { 13 * DIGIT_WIDTH, 0, COLON_WIDTH, COLON_HEIGHT };
		texture_render(&digits_texture, COLON_X, COLON_Y, &clip);
	}
}

void view_paint()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	render_char(digit1, 0);
	render_char(digit2, DIGIT_WIDTH);
	render_colon(colon);
	render_char(digit3, DIGIT_WIDTH * 2 + COLON_WIDTH);
	render_char(digit4, DIGIT_WIDTH * 2 + COLON_WIDTH + DIGIT_WIDTH);

	SDL_RenderPresent(g_renderer);
}

