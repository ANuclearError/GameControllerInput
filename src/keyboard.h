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

int get_position(SDL_Keycode key);

void update_cursor(SDL_Keycode key, Cursor* k_cursor);

#endif // KEYBOARD_H