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

Command get_key_command(SDL_Keycode key)
{
	if (key == SDLK_w || key == SDLK_a || key == SDLK_s || key == SDLK_d)
	{
		return COMMAND_MOVE;
	}

	if (key >= SDLK_KP_1 && key <= SDLK_KP_9)
	{
		return COMMAND_SELECT;
	}
	
	if (key == SDLK_SPACE)
	{
		return COMMAND_SPACE;
	}

	if (key == SDLK_BACKSPACE)
	{
		return COMMAND_BACKSPACE;
	}

	if (key == SDLK_RETURN)
	{
		return COMMAND_ENTER;
	}
	return COMMAND_TOTAL;
}

void key_update_cursor(SDL_Keycode key, Cursor* k_cursor)
{
	if (key >= SDLK_KP_1 && key <= SDLK_KP_9)
	{
		int selected = key - NUMPAD_START; // Get value from 1-9

		// Need to handle numpad format
		if (selected > 6) {
			k_cursor->key = selected - 7;
		}
		else if (selected < 4)
		{
			k_cursor->key = selected + 5;
		}
		else
		{
			k_cursor->key = selected - 1;
		}
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