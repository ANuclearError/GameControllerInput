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
 * Attempts to create the window.
 *
 * @return true if creation successful, otherwise returns false.
 */
bool view_init()
{
	printf("Creating view\n");

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
 * Refreshes the display to match current situation.
 */
void repaint()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, BKGRD.r, BKGRD.g, BKGRD.b, BKGRD.a);
	SDL_RenderFillRect(renderer, NULL);
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