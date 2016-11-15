/******************************************************************************
 *
 * @file    Keydata.h
 * @author  Aidan O'Grady
 * @date    2016-11-11
 * @version 0.2
 *
 * The data required for representing the keyboard and its current state.
 *
 ******************************************************************************/
#ifndef KEYDATA_H
#define KEYDATA_H

#define ROWS 4
#define COLUMNS 10

/**
 * Keys have certain modes that can they be in, they can be keys that are being
 * hovered over by the selection matrix, and keys that have been selected. The
 * Mode enum handles the difference between each of these modes.
 */
typedef enum Mode
{
	MODE_STANDARD,
	MODE_HOVER,
	MODE_SELECTED,
	MODE_TOTAL
} Mode;

/**
 * The Cursor struct defines the cursor that is used to move between areas of
 * keyboard.
 */
typedef struct Cursor
{
	/**
	 * The X position of the cursor matrix.
	 */
	int x;

	/**
	 * The Y position of the cursor matrix.
	 */
	int y;

	/**
	 * The length and breadth of the matrix.
	 */
	int size;

	/**
	 * The currently selected key in the matrix, defaults to -1 if no key is
	 * seected.
	 */
	int selected;
} Cursor;

/**
 * A lower-case keyboard. For the purposes of prototyping, upper case and
 * symbols have been ignored, since they are not being controlled in a novel
 * way.
 */
const char KEYBOARD[ROWS][COLUMNS] = {
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
    {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\''},
	{'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '?'}
};

#endif // KEYDATA_H