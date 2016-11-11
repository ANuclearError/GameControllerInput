/******************************************************************************
*
 * @file    view.h
 * @author  Aidan O'Grady
 * @date    2016-11-11
 * @version 0.1
 *
 * Contains all the variables and functions required for the view.
 *
 ******************************************************************************/
#ifndef VIEW_H
#define VIEW_H

/**
 * The window that displays everything in relation to the keyboard.
 */
extern SDL_Window* window;

/**
 * Attempts to create the window.
 *
 * @return true if creation successful, otherwise returns false.
 */
bool view_init();

/**
 * Destroys everything relating to view.
 */
void view_close();

#endif // VIEW_H