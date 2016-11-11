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
 * The size of the main window.
 */
const struct Size WIN_SIZE = {1555, 525};

/**
 * The size of the keys.
 */
const struct Size KEY_SIZE = {150, 100};

#endif // VIEWDATA_H
