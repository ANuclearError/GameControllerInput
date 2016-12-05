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
#include "keydata.h"
#include "controller.h"
#include "keyboard.h"
#include "view.h"

/**
 * A lower-case keyboard. For the purposes of prototyping, upper case and
 * symbols have been ignored, since they are not being controlled in a novel
 * way.
 */
const char KEYBOARD[ROWS][COLS] = {
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
    {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\''},
    {'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '?'}
};

/**
 * The keyboard's cursor
 */
Cursor k_cursor = {0, 0, 2, -1};

/**
 * The user input array
 */
char input[64];

/**
 * The prompt the user should type in to measure efficiency
 */
char prompt[64] = "the quick brown fox jumped over the lazy dog.";

/**
 * The position where text is being entered.
 */
int pos = 0;

/**
 * The number of errors the user has made.
 */
int errors = 0;

/**
 * The time the user started typing.
 */
Uint32 start_time;

/**
 * The action for moving.
 */
Action move_action;

/**
 * The action for spacing.
 */
 Action space_action;

/**
 * The action for backspacing.
 */
 Action bspace_action;

/**
 * The action for selecting.
 */
 Action select_action;

/**
 * Returns the mode that the given position in keyboard matrix corresponds to.
 *
 * @param x the x position
 * @param y the y position
 * @return selected mode if entered, hover mode is hovered, standard otherwise.
 */
int get_mode(int x, int y)
{
    int x_start = k_cursor.x;
    int x_end = k_cursor.x + k_cursor.size;
    int y_start = k_cursor.y;
    int y_end = k_cursor.y + k_cursor.size;

    if (x >= x_start && x < x_end && y >= y_start && y < y_end)
    {
        if (x == k_cursor.x + (k_cursor.key % k_cursor.size) &&
            y == k_cursor.y + (k_cursor.key / k_cursor.size))
        {
            return MODE_SELECTED;
        }
        return MODE_HOVER;
    }
    
    return MODE_STANDARD;
}

/**
 * Returns the character that has been selected by user.
 *
 * @return selected character
 */
char get_selected_key()
{
    int x = (k_cursor.key % k_cursor.size);
    int y = (k_cursor.key / k_cursor.size);
    return KEYBOARD[k_cursor.y + y][k_cursor.x + x];
}

/**
 * Adds space to input.
 */
void space()
{
    input[pos]= ' ';
    if (input[pos] != prompt[pos])
    {
        errors++;
        printf("Error %d\n", errors);
    }
    pos++;
}

/**
 * Performs backspace on input.
 */
void backspace()
{
    pos = (pos - 1 > 0) ? pos - 1 : 0;
    input[pos] = '\0';
}

/**
 * Returns if the user's entered text matches the given prompt.
 */
bool enter()
{
    if(strcmp(input, prompt) == 0)
    {
        Uint32 time = SDL_GetTicks() - start_time;
        printf("Time taken %d Errors %d\n", time, errors);
        return true;
    }
    return false;
}

void handle_input()
{
    if (pos == 0)
    {
        start_time = SDL_GetTicks();
    }
    
    if (pos < 127)
    {
        input[pos] = get_selected_key();
        if (input[pos] != prompt[pos])
        {
            errors++;
            printf("Error %d\n", errors);
        }
        pos++;
    }
}

/**
 * Refreshes the display, handling rendering of characters and input.
 */
void refresh()
{
    clear_render();
    render_input(input, prompt, pos);
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            char key = KEYBOARD[i][j];
            // j and i are swapped in order due to fact that j is x column and
            // i is row column, it confused me.
            int mode = get_mode(j, i);
            render_key(j, i, key, mode);
        }
    }
    repaint();
}

/**
 * Displays the splash screen, and returns whether or not the user has
 * decided to quite the program.
 *
 * @return true if user pressed to continue, false if user pressed close button.
 */
bool splash()
{
    SDL_Event e;

    bool splash = true;
    display_splash();
    while (splash)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                splash = false;
                return false;
            }
            else if (e.type == SDL_CONTROLLERBUTTONDOWN)
            {
                splash = false;
                return true;
            }
        }
    }
    return true;
}

/**
 * #include <SDL.h>
 *
 * The main control loop of the system, handling events etc.
 */
int main(int argc, char* args[])
{
    // Init everything
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL_Error initialisation: %s\n", SDL_GetError());
        return -1;
    }
    if (!(view_init() && controller_init()))
    {
        printf("Failed to initialise.\n");
        return -1;
    }

    move_action.act = false;
    move_action.last = SDL_GetTicks();
    space_action.act = false;
    space_action.last = SDL_GetTicks();
    bspace_action.act = false;
    bspace_action.last = SDL_GetTicks();
    select_action.act = false;
    select_action.last = SDL_GetTicks();

    bool run = splash();
    refresh();

    SDL_Event e;
    while (run)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }
            else if (e.type == SDL_CONTROLLERBUTTONDOWN)
            {
                Command com = get_command(e.cbutton.button);
                switch (com)
                {
                    case COMMAND_MOVE:
                    move_action.act = true;
                    break;
                    case COMMAND_SPACE:
                    space_action.act = true;
                    break;
                    case COMMAND_BACKSPACE:
                    bspace_action.act = true;
                    break;
                    case COMMAND_ENTER:
                    run = !enter();
                    refresh();
                    break;
                    default:
                    break;
                }
            }
            else if (e.type == SDL_CONTROLLERBUTTONUP)
            {
                Command com = get_command(e.cbutton.button);
                switch (com)
                {
                    case COMMAND_MOVE:
                    move_action.act = false;
                    break;
                    case COMMAND_SPACE:
                    space_action.act = false;
                    break;
                    case COMMAND_BACKSPACE:
                    bspace_action.act = false;
                    break;
                    default:
                    break;
                }
            }
        }

        if (move_action.act && SDL_GetTicks() - move_action.last > 200)
        {
            move(&k_cursor);
            move_action.last = SDL_GetTicks();
        }

        if (space_action.act && SDL_GetTicks() - space_action.last > 200)
        {
            space();
            space_action.last = SDL_GetTicks();
        }

        if (bspace_action.act && SDL_GetTicks() - bspace_action.last > 200)
        {
            backspace();
            bspace_action.last = SDL_GetTicks();
        }

        if (!select_action.act)
        {
            select(&k_cursor);
            if (k_cursor.key > -1)
            {
                select_action.act = true;
                select_action.last = SDL_GetTicks();
                handle_input();
            }
        }
        else if (select_action.act && SDL_GetTicks() - select_action.last > 200)
        {
            select_action.act = false;
            k_cursor.key = -1;
            refresh();
        }

        refresh();
    }

    controller_close();
    view_close();
    return 0;
}