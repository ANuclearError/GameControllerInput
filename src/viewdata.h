/******************************************************************************
*
 * @file    viewdata.h
 * @author  Aidan O'Grady
 * @date    2016-11-11
 * @version 0.1
 *
 * Contains the structs and constants required for the view.
 *
 ******************************************************************************/
#ifndef VIEWDATA_H
#define VIEWDATA_H

/**
 * Structure for holding pixel dimensions of various on-screen objects.
 */
struct Size
{
	/**
	 * The width of the object.
	 */
	int w;

	/**
	 * The width of the object.
	 */
	int h;
};

/**
 * The gap between objects on screen.
 */
const int GAP = 5;

/**
 * The height reserved for the text box displaying user input.
 */
const int TEXT_BOX_HEIGHT = 100;

/**
 * The height of image displaying icons.
 */
const int ICONS_HEIGHT = 130;

/**
 * The size of the main window.
 */
const struct Size WIN_SIZE = {1555, 655};

/**
 * The size of the keys.
 */
const struct Size KEY_SIZE = {150, 100};

/**
 * The background colour of the keyboard.
 */
const SDL_Color BG_COL = {21, 21, 21, SDL_ALPHA_OPAQUE};

/**
 * The standard colour of keys
 */
const SDL_Color KEY_COL = {75, 75, 75, SDL_ALPHA_OPAQUE};

/**
 * The standard colour of keys
 */
const SDL_Color HOVER_COL = {100, 150, 101, SDL_ALPHA_OPAQUE};

/**
 * The standard colour of keys
 */
const SDL_Color ENTER_COL = {76, 175, 80, SDL_ALPHA_OPAQUE};

/**
 * The colour of the characters being rendered.
 */
const SDL_Color CHAR_COL = {255, 255, 255, SDL_ALPHA_OPAQUE};

/**
 * The colour of the prompt text being displayed.
 */
const SDL_Color PROMPT_COL = {50, 50, 50, SDL_ALPHA_OPAQUE};

/**
 * The colour of characters that do not match the prompt.
 */
const SDL_Color ERR_COL = {255, 0, 0, SDL_ALPHA_OPAQUE};

#endif // VIEWDATA_H
