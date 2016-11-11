/******************************************************************************
*
 * @file    main.cpp
 * @author  Aidan O'Grady
 * @date    2016-11-01
 * @version 0.1
 *
 * The controller of the system, creating the view and model of the application
 * and handling interaction between them.
 *
 ******************************************************************************/
#include <SDL2/SDL.h>
#include "view.h"

/**
 * #include <SDL.h>
 *
 * The main control loop of the system, handling events etc.
 */
int main(int argc, char* args[])
{
    View keyboard_view(1555, 525);
    bool run = true;
    while (run)
    {
        SDL_Event event = keyboard_view.get_event();
        switch (event.type)
        {
            case SDL_QUIT:
                run = false;
                break;
            default:
                break;
        }
    }
    keyboard_view.close();
    return 0;
}