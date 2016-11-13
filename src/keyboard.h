/******************************************************************************
*
 * @file    keyboard.h
 * @author  Aidan O'Grady
 * @date    2016-11-11
 * @version 0.1
 *
 * Contains the keyboard.
 *
 ******************************************************************************/
#ifndef KEYBOARD_H
#define KEYBOARD_H

#define ROWS 4
#define COLUMNS 10

typedef enum Case
{
	CASE_LOWER,
	CASE_UPPER,
	CASE_TOTAL
} Case;

typedef enum Mode
{
	MODE_STANDARD,
	MODE_HOVER,
	MODE_SELECTED,
	MODE_TOTAL
} Mode;

typedef struct Keyboard
{
	Case k_case;
	char k_keys[ROWS][COLUMNS];
} Keyboard;

typedef struct Cursor
{
	int x;
	int y;
	int size;
	int selected;
} Cursor;

const Keyboard KEYBOARDS[CASE_TOTAL] = {
	{	
		CASE_LOWER,
		{
	        {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
	        {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
	        {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\''},
			{'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '?'}
		}
	},
	{
		CASE_UPPER,
		{
	        {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
	        {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
	        {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '\''},
			{'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '?'}
		}	
	}
};

#endif // KEYBOARD_H