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
 * Returns the command determined by the controller button pressed.
 *
 * @param e the button that was pressed.
 * @return command
 */
Command get_command(SDL_GameControllerButton e);

/**
 * Updates the given cursor with information taken from controller.
 *
 * @param k_cursor the cursor controlling keyboard.
 */
void move(Cursor* k_cursor);

/**
 * Graceful close of the controller.
 */
void controller_close();

#endif // CONTROLLER_H