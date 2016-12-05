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
Cursor k_cursor = {0, 0, 3, -1};

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

    bool do_move = false;
    Uint32 last_move = SDL_GetTicks();
    bool do_space = false;
    Uint32 last_space = SDL_GetTicks();
    bool do_backspace = false;
    Uint32 last_backspace = SDL_GetTicks();

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
                    do_move = true;
                    break;
                    case COMMAND_SPACE:
                    do_space = true;
                    break;
                    case COMMAND_BACKSPACE:
                    do_backspace = true;
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
                    do_move = false;
                    break;
                    case COMMAND_SPACE:
                    do_space = false;
                    break;
                    case COMMAND_BACKSPACE:
                    do_backspace = false;
                    break;
                    default:
                    break;
                }
            }
        }

        if (do_move && SDL_GetTicks() - last_move > 150)
        {
            move(&k_cursor);
            last_move = SDL_GetTicks();
        }

        if (do_space && SDL_GetTicks() - last_space > 150)
        {
            space();
            last_space = SDL_GetTicks();
        }

        if (do_backspace && SDL_GetTicks() - last_backspace > 150)
        {
            backspace();
            last_backspace = SDL_GetTicks();
        }
        refresh();
    }

    controller_close();
    view_close();
    return 0;
}