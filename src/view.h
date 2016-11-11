/******************************************************************************
*
 * @file    view.cpp
 * @author  Aidan O'Grady
 * @date    2016-11-01
 * @version 0.1
 *
 * Contains the components required for creating a window, and displaying
 * information on the window.
 *
 ******************************************************************************/
#ifndef VIEW_H
#define VIEW_H

class View
{
private:
    /**
     * The SFML window that displays all information.
     */
    SDL_Window* window;

public:
    /**
     * Constructs a new View.
     *
     * @param width the width of the View's window
     * @param height the height of the View's window
     */
    View(int width, int height);

    /**
     * Waits for an Event to occur and returns.
     *
     * @return the first event from queue
     */
    SDL_Event get_event();

    /**
     * Closes the view's window.
     */
    void close();
};
#endif // VIEW_H