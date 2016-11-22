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
#include <math.h>
#include "keydata.h"
#include "controller.h"

/**
 * The deadzone of the controller, input is ignored inside this limit.
 */
const int DEAD_ZONE = 32767 / 3;

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
 * Returns the command determined by the controller button pressed.
 *
 * @param e the button that was pressed.
 * @return command
 */
Command get_command(SDL_GameControllerButton e)
{
    if (e == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
    {
        return COMMAND_BACKSPACE;
    }

    if (e == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
    {
        return COMMAND_SPACE;
    }

    if (e == SDL_CONTROLLER_BUTTON_START)
    {
        return COMMAND_ENTER;
    }
    return COMMAND_TOTAL;
}

/**
 * Updates the given cursor with information taken from controller.
 *
 * @param k_cursor the cursor controlling keyboard.
 */
void move(Cursor* k_cursor)
{
    int x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    int y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
    if (x > DEAD_ZONE)
    {
        k_cursor->x = (k_cursor->x + 1) % (COLS - k_cursor->size + 1);
    }
    else if (x < -DEAD_ZONE)
    {
        k_cursor->x = k_cursor->x - 1;
        if (k_cursor->x < 0)
        {
            k_cursor->x = COLS - k_cursor->size;
        }
    }
    else if (y > DEAD_ZONE)
    {
        k_cursor->y = (k_cursor->y + 1) % (ROWS - k_cursor->size + 1);
    }
    else if (y < -DEAD_ZONE)
    {
        k_cursor->y = k_cursor->y - 1;
        if (k_cursor->y < 0)
        {
            k_cursor->y = ROWS - k_cursor->size;
        }
    }
}

/**
 * Updates the given cursor with information taken from controller.
 *
 * @param k_cursor the cursor controlling keyboard.
 */
void select(Cursor* k_cursor)
{
    int x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
    int y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
    if (SDL_GameControllerGetButton(controller,
                                    SDL_CONTROLLER_BUTTON_RIGHTSTICK))
    {
        k_cursor->key = 4;
    }
    else
    {
        if (x < -DEAD_ZONE)
        {
            x = 0;
        }
        else if (x > DEAD_ZONE)
        {
            x = 2;
        }
        else
        {
            x = 1;
        }

        if (y < -DEAD_ZONE)
        {
            y = 0;
        }
        else if (y > DEAD_ZONE)
        {
            y = 2;
        }
        else
        {
            y = 1;
        }


         if (x != 1 || y != 1)
         {
            k_cursor->key = k_cursor->size * y + x;
         }
    }
}

/**
 * Graceful close of the controller.
 */
void controller_close()
{
    SDL_GameControllerClose(controller);
    controller = NULL;
}