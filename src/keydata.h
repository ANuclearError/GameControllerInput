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
#define COLS 10

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
 * There are various commands that could be read from input, such as moving the
 * cursor or wishing to add a space. The Command enum contains all such actions.
 */
typedef enum Command
{
	COMMAND_MOVE,
	COMMAND_SELECT,
	COMMAND_SPACE,
	COMMAND_BACKSPACE,
	COMMAND_ENTER,
	COMMAND_TOTAL
} Command;

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
	 * selected.
	 */
	int key;
} Cursor;
#endif // KEYDATA_H