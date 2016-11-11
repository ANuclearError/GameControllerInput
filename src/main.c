/******************************************************************************
*
 * @file    main.cpp
 * @author  Aidan O'Grady
 * @date    2016-11-11
 * @version 0.1
 *
 * The controller of the system, creating the view and model of the application
 * and handling interaction between them.
 *
 ******************************************************************************/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "keyboard.h"
#include "view.h"

int k_index = 0;

/**
 * #include <SDL.h>
 *
 * The main control loop of the system, handling events etc.
 */
int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL_Error initialisation: %s\n", SDL_GetError());
        return -1;
    }

    if (!view_init())
    {
        printf("Failed to initialise view\n");
        return -1;
    }

    bool run = true;
    SDL_Event e;

    repaint();

    while (run)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }
        }
    }

    view_close();
    return 0;
}