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
 * The controller to read data from.
 */
SDL_GameController* c = NULL;

/**
 * Initialises the controller, ensuring that it is connected.
 */
bool controller_init() {
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            c = SDL_GameControllerOpen(i);
            if (c)
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

    if (c == NULL)
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

    if (e == SDL_CONTROLLER_BUTTON_DPAD_UP ||
        e == SDL_CONTROLLER_BUTTON_DPAD_DOWN ||
        e == SDL_CONTROLLER_BUTTON_DPAD_LEFT ||
        e == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
    {
        return COMMAND_MOVE;
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
    if (SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
    {
        k_cursor->x = (k_cursor->x + 1) % (COLS - k_cursor->size + 1);
    }
    else if (SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
    {
        k_cursor->x = k_cursor->x - 1;
        if (k_cursor->x < 0)
        {
            k_cursor->x = COLS - k_cursor->size;
        }
    }
    
    if (SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
    {
        k_cursor->y = (k_cursor->y + 1) % (ROWS - k_cursor->size + 1);
    }
    else if (SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_DPAD_UP))
    {
        k_cursor->y = k_cursor->y - 1;
        if (k_cursor->y < 0)
        {
            k_cursor->y = ROWS - k_cursor->size;
        }
    }
}

/**
 * Returns whether or not the given value is outside of the deadzone.
 *
 * @param val the axis value
 * @return true if val outside of deadzone.
 */
bool out_dead_zone(int val)
{
    return (val <-DEAD_ZONE) || (val > DEAD_ZONE);
}

/**
 * Updates the given cursor with information taken from controller.
 *
 * @param k_cursor the cursor controlling keyboard.
 */
void select(Cursor* k_cursor)
{
    int x = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_RIGHTX);
    int y = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_RIGHTY);
    if (SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_RIGHTSTICK))
    {
        k_cursor->key = 4;
    }
    else if (out_dead_zone(x) || out_dead_zone(y))
    {
        x -= MIN_AXIS;
        y -= MIN_AXIS;
        int div = (MAX_AXIS - MIN_AXIS) / k_cursor->size;
        x = x / div;
        if (x == k_cursor->size)
            x--;
        y = y / div;
        if (y == k_cursor->size)
            y--;
        k_cursor->key = (y * k_cursor->size) + x;
    }
}

/**
 * Graceful close of the controller.
 */
void controller_close()
{
    SDL_GameControllerClose(c);
    c = NULL;
}