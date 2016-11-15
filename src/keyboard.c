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