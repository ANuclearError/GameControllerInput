/******************************************************************************
*
 * @file    view.cpp
 * @author  Aidan O'Grady
 * @date    2016-11-01
 * @version 0.1
 *
 * The implementation of the View class defined in view.h
 *
 ******************************************************************************/
#include <SFML/Window.hpp>
#include "view.h"
#include <iostream>

/**
 * Constructs a new View. An SFML window is created with the given width and
 * height, and is provided a constant name. The window is given a framerate
 * limit as well.
 *
 * @param width the width of the View's window
 * @param height the height of the View's window
 */
View::View(int width, int height)
{
    window.create(sf::VideoMode(width, height), sf::String("Keyboard")); 
    window.setFramerateLimit(60);
    std::cout << "Window opened\n";
}

/**
 * Waits for an Event to occur and returns.
 *
 * @return the first event from queue
 */
sf::Event View::get_event()
{
    sf::Event event;
    while (window.waitEvent(event))
    {
        return event;
    }
    return event;
}

/**
 * #include <SDL.h>
 *
 * Presents the current render to the window.
 *
 * Returns whether or not the view's window is open. This is a wrapper function
 * for the Window class.
 *
 * @return whether or not the window is still open.
 */
bool View::is_open()
{
    return window.isOpen();
}

/**
 * Closes the view's window. This is a wrapper function for the Window's close
 * function.
 */
void View::close()
{
    window.close();
}