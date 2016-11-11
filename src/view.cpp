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
#include <SDL2/SDL.h>
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
    std::cout << "Initialising view\n";
    window = SDL_CreateWindow("Keyboard",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL){
        std::cout << "SDL_Error creating window: " << SDL_GetError() << "\n";
    }
    std::cout << "Window opened\n";
}

/**
 * Waits for an Event to occur and returns.
 *
 * @return the first event from queue
 */
SDL_Event View::get_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        return event;
    }
    return event;
}

/**
 * Closes the view's window. This is a wrapper function for the Window's close
 * function.
 */
void View::close()
{
    std::cout << "Beginning shutdown\n";
    SDL_DestroyWindow(window);
    window = NULL;
    std::cout << "Shutdown successful\n";
}