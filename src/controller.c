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
#include "controller.h"
#include "keydata.h"

/**
 * The deadzone of the controller, input is ignored inside this limit.
 */
const int DEAD_ZONE = 8000;

/**
 * The controller to read data from.
 */
SDL_Joystick* controller = NULL;

/**
 * Initialises the controller, ensuring that it is connected.
 */
bool controller_init() {
    if (SDL_NumJoysticks() < 1)
    {
        printf("Warning: no joysticks connected!\n");
        return false;
    }
    else
    {
        controller = SDL_JoystickOpen(0);
        if (controller == NULL)
        {
            printf("SDL_Error opening controller %s\n", SDL_GetError());
            return false;
        }
    }
    return true;
}

/**
 * Graceful close of the controller.
 */
void controller_close()
{
    SDL_JoystickClose(controller);
    controller = NULL;
}