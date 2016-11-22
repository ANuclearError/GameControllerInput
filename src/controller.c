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
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "keydata.h"
#include "controller.h"

/**
 * The deadzone of the controller, input is ignored inside this limit.
 */
const int DEAD_ZONE = 8000;

/**
 * The controller to read data from.
 */
SDL_GameController* controller = NULL;

/**
 * Initialises the controller, ensuring that it is connected.
 */
bool controller_init() {
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            if (controller)
            {
                return true;
            }
            else
            {
                printf("SDL_Error controller: %s\n", SDL_GetError());
                return false;
            }
        }
    }

    if (controller == NULL)
    {
        printf("SDL_Error controller: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

/**
 * Graceful close of the controller.
 */
void controller_close()
{
    SDL_GameControllerClose(controller);
    controller = NULL;
}