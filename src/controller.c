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
const int DEAD_ZONE = 16000;

/**
 * The controller to read data from.
 */
SDL_GameController* controller = NULL;

/**
 * Initialises the controller, ensuring that it is connected.
 */
bool controller_init()
{
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            if (controller == NULL)
            {
                printf("SDL_Error opening controller %s\n", SDL_GetError());
                return false;
            }
            return true;
        }
    }
    if (controller == NULL)
    {
        printf("SDL_Error opening controller %s\n", SDL_GetError());
        return false;
    }
    return true;
}

/**
 * Converts a key code into a command.
 *
 * @param key the key that was pressed
 * @return command
 */
Command get_command(SDL_Event e)
{
    if (e.type == SDL_CONTROLLERAXISMOTION)
    {
        if (e.caxis.value > DEAD_ZONE || e.caxis.value < -DEAD_ZONE)
        {
            switch (e.caxis.axis)
            {
                case SDL_CONTROLLER_AXIS_LEFTX:
                case SDL_CONTROLLER_AXIS_LEFTY:
                return COMMAND_MOVE;
                break;
                case SDL_CONTROLLER_AXIS_RIGHTX:
                case SDL_CONTROLLER_AXIS_RIGHTY:
                return COMMAND_SELECT;
                break;
                default:
                break;
            }
        }
    }
    else if (e.type == SDL_CONTROLLERBUTTONDOWN)
    {
        if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK)
        {
            return COMMAND_SELECT;
        }
        else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
        {
            return COMMAND_BACKSPACE;
        }
        else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
        {
            return COMMAND_SPACE;
        }
        else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_START)
        {
            return COMMAND_ENTER;
        }
    }
    return COMMAND_TOTAL;
}

void move(Cursor* k_cursor)
{
    Sint16 x_axis, y_axis;
    x_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    y_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

    if (x_axis > DEAD_ZONE) // Right
    {
        k_cursor->x = (k_cursor->x + 1) % (COLS - k_cursor->size + 1);
    }
    else if (x_axis < -DEAD_ZONE) // Left
    {
        k_cursor->x = k_cursor->x - 1;
        if (k_cursor->x < 0)
        {
            k_cursor->x = COLS - k_cursor->size;
        }
    }
    else if (y_axis > DEAD_ZONE) // Down
    {
        k_cursor->y = (k_cursor->y + 1) % (ROWS - k_cursor->size + 1);
    }
    else if (y_axis < -DEAD_ZONE) // Up
    {
        k_cursor->y = k_cursor->y - 1;
        if (k_cursor->y < 0)
        {
            k_cursor->y = ROWS - k_cursor->size;
        }
    }
}

void update_cursor(Cursor* k_cursor)
{
    move(k_cursor);
}

/**
 * Graceful close of the controller.
 */
void controller_close()
{
    SDL_GameControllerClose(controller);
    controller = NULL;
}