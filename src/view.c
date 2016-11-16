/******************************************************************************
*
 * @file    view.c
 * @author  Aidan O'Grady
 * @date    2016-11-11
 * @version 0.1
 *
 * Contains the implementation of functions required for displaying the state of
 * the keyboard.
 *
 ******************************************************************************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "viewdata.h"
#include "view.h"

/**
 * The window that displays everything in relation to the keyboard.
 */
SDL_Window* window = NULL;

/**
 * The renderer, rendering keys and current position of cursor.
 */
SDL_Renderer* renderer = NULL;

/**
 * The font for rendering characters.
 */
TTF_Font* font = NULL;

/**
 * Pointer to the surface used to draw a character to the screen.
 */
SDL_Surface* surface = NULL;

/**
 * Pointer to the texture used to draw a character to screen.
 */
SDL_Texture* texture = NULL;

/**
 * The rectangle containing the character 
 */
SDL_Rect char_rect;

/**
 * The area where the input text is added.
 */
SDL_Rect input_rect;

/**
 * Attempts to create the window.
 *
 * @return true if creation successful, otherwise returns false.
 */
bool view_init()
{
	printf("Creating view\n");

    if (TTF_Init() == -1)
    {
        printf("TTF_Error initialising: %s\n", TTF_GetError());
        return false;
    }

    font = TTF_OpenFont("arial.ttf", 36);
    if (font == NULL)
    {
        printf("TTF_Error opening font: %s\n", TTF_GetError());
        return false;
	}

	window = SDL_CreateWindow("Keyboard",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_SIZE.w, WIN_SIZE.h, SDL_WINDOW_SHOWN
	);

	if (window == NULL)
	{
		printf("SDL_Error creating window: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("SDL_Error creating renderer: %s\n", SDL_GetError());
		return false;
	}

	printf("View created\n");
	return true;
}

/**
 * Renders the input text.
 *
 * @param The input to be displayed
 */
void render_input(char input[])
{
    surface = TTF_RenderText_Blended(font, input, CHAR_COL);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &input_rect.w, &input_rect.h);
    input_rect.x = 50;
    input_rect.y = (TEXT_BOX_HEIGHT / 2) - (input_rect.h / 2);
	SDL_RenderCopy(renderer, texture, NULL, &input_rect);
	// Now need to ensure we aren't eating 2 gigs of RAM.
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = NULL;
	texture = NULL;
}

/**
 * Renders the key using the given position, character and mode.
 *
 * @param x the x position on matrix
 * @param y the y position on matrix
 * @param key the character to be rendered
 * @param mode the mode this key is in (see Mode in Keyboard.h)
 */
void render_key(int x, int y, char key, int mode)
{	
	SDL_Color color;
	switch (mode) // Choose colour of key based on mode.
	{
		case 1:
			color = HOVER_COL;
			break;
		case 2:
			color = ENTER_COL;
			break;
		default:
			color = KEY_COL;
			break;
	}
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect key_rect = {
        GAP + ((KEY_SIZE.w + GAP) * x),
        GAP + ((KEY_SIZE.h + GAP) * y) + TEXT_BOX_HEIGHT,
        KEY_SIZE.w,
        KEY_SIZE.h
    };
	SDL_RenderFillRect(renderer, &key_rect);

	// Render the character
    surface = TTF_RenderText_Blended(font, &key, CHAR_COL);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &char_rect.w, &char_rect.h);
    char_rect.x = key_rect.x + (key_rect.w / 2) - (char_rect.w / 2);
    char_rect.y = key_rect.y + (key_rect.h / 2) - (char_rect.h / 2);
    SDL_RenderCopy(renderer, texture, NULL, &char_rect);

    // Now need to ensure we aren't eating 2 gigs of RAM.
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = NULL;
	texture = NULL;
}

/**
 * Clears the current screen.
 */
void clear_render()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, BG_COL.r, BG_COL.g, BG_COL.b, BG_COL.a);
	SDL_RenderFillRect(renderer, NULL);
}

/**
 * Refreshes the display to match current situation.
 */
void repaint()
{
	SDL_RenderPresent(renderer);
}

/**
 * Destroys everything relating to view.
 */
void view_close()
{
	printf("Closing view\n");
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	printf("View closed\n");
}