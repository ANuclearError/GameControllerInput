/******************************************************************************
 *
 * @file    keyboard.h
 * @author  Aidan O'Grady
 * @date    2016-11-15
 * @version 0.3
 *
 * The keyboard version of user input. This simulates controller input using
 * keyboards.
 *
 ******************************************************************************/
#include <SDL2/SDL.h>
#include "keydata.h"
#include "keyboard.h"

int get_position(SDL_Keycode key)
{
	switch (key)
	{
		case SDLK_KP_1:
		return 6;
		break;
		case SDLK_KP_2:
		return 7;
		break;
		case SDLK_KP_3:
		return 8;
		break;
		case SDLK_KP_4:
		return 3;
		break;
		case SDLK_KP_5:
		return 4;
		break;
		case SDLK_KP_6:
		return 5;
		break;
		case SDLK_KP_7:
		return 0;
		break;
		case SDLK_KP_8:
		return 1;
		break;
		case SDLK_KP_9:
		return 2;
		break;
	}
	return -1;
}

void update_cursor(SDL_Keycode key, Cursor* k_cursor)
{
    if (key >= SDLK_KP_1 && key <= SDLK_KP_9)
	{
		k_cursor->selected = get_position(key);
	}
	else if (key == SDLK_w)
	{
	    k_cursor->y = k_cursor->y - 1;
	    if (k_cursor->y < 0)
	    {
	        k_cursor->y = ROWS - k_cursor->size;
	    }
	}
	else if (key == SDLK_s)
	{
	    k_cursor->y = (k_cursor->y + 1) % (ROWS - k_cursor->size + 1);
	}
	else if (key == SDLK_a)
	{
	    k_cursor->x = k_cursor->x - 1;
	    if (k_cursor->x < 0)
	    {
	        k_cursor->x = COLS - k_cursor->size;
	    }
	}
	else if (key == SDLK_d)
	{
	    k_cursor->x = (k_cursor->x + 1) % (COLS - k_cursor->size + 1);
	}
}