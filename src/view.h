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
 * Attempts to create the window.
 *
 * @return true if creation successful, otherwise returns false.
 */
bool view_init();

/**
 * Clears the current screen.
 */
void clear_render();

/**
 * Renders a key with the given position and cursor state.
 */
void render_key(int x, int y, char key, int mode);

/**
 * Refreshes the display to match current situation.
 */
void repaint();

/**
 * Destroys everything relating to view.
 */
void view_close();

#endif // VIEW_H