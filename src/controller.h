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

void move(Cursor* k_cursor);

/**
 * Graceful close of the controller.
 */
void controller_close();

#endif // CONTROLLER_H