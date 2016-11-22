/******************************************************************************
 *
 * @file    controller.h
 * @author  Aidan O'Grady
 * @date    2016-11-21
 * @version 0.4
 *
 * The controller version of user input. Inputs from a controller are converted
 * into commands recognized by the system.
 *
 ******************************************************************************/
#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * Initialises the controller, ensuring that it is connected.
 */
bool controller_init();

/**
 * Converts a key code into a command.
 *
 * @param key the key that was pressed
 * @return command
 */
//Command get_command(SDL_Keycode key);

/**
 * Updating the cursor to reflect the user input.
 *
 * @param key the key that was pressed
 * @param k_cursor the cursor struct containing information
 */
//void update_cursor(SDL_Keycode key, Cursor* k_cursor);

/**
 * Graceful close of the controller.
 */
void controller_close();

#endif // CONTROLLER_H