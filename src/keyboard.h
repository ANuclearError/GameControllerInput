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
#ifndef KEYBOARD_H
#define KEYBOARD_H

/**
 * The Where the numpad key ids start from.
 */
#define NUMPAD_START 1073741912

/**
 * Converts a key code into a command.
 *
 * @param key the key that was pressed
 * @return command
 */
Command get_command(SDL_Keycode key);

/**
 * Updating the cursor to reflect the user input.
 *
 * @param key the key that was pressed
 * @param k_cursor the cursor struct containing information
 */
void update_cursor(SDL_Keycode key, Cursor* k_cursor);

#endif // KEYBOARD_H