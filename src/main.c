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
 * Refreshes the display, handling rendering of characters and input.
 */
void refresh()
{
    clear_render();
    render_input(input, prompt);
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
    if (!view_init())
    {
        printf("Failed to initialise view\n");
        return -1;
    }

    bool move = true;
    bool select = false;
    Uint32 last_move = SDL_GetTicks();
    Uint32 last_select = SDL_GetTicks();

    bool run = true;
    SDL_Event e;
    while (run)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                Command com = get_command(e.key.keysym.sym);
                switch (com)
                {
                    case COMMAND_MOVE:
                    case COMMAND_SELECT:
                    update_cursor(e.key.keysym.sym, &k_cursor);
                    if (k_cursor.key > -1 && !select)
                    {
                        select = true;
                        last_select = SDL_GetTicks();
                        if (pos == 0)
                        {
                            start_time = last_select;
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
                    else if (!move)
                    {
                        move = true;
                        last_move = SDL_GetTicks();
                    }
                    break;
                    case COMMAND_SPACE:
                    input[pos] = ' ';
                    pos++;
                    refresh();
                    break;
                    case COMMAND_BACKSPACE:
                    pos = (pos - 1 > 0) ? pos - 1 : 0;
                    input[pos] = '\0';
                    refresh();
                    break;
                    case COMMAND_ENTER:
                    if (strcmp(input, prompt) == 0) {
                        Uint32 time = SDL_GetTicks() - start_time;
                        printf("Time taken %d Errors %d\n", time, errors);
                        run = false;
                        SDL_Delay(5000);
                    }
                    else {
                        printf("You ain't down, keep going\n");
                    }
                    break;
                    default:
                    break;
                }

            }
        }
        if (move && (SDL_GetTicks() - last_move) > 67)
        {
            move = false;
            refresh();
        }
        else if (select && (SDL_GetTicks() - last_select) > 67)
        {
            select = false;
            k_cursor.key = -1;
            refresh();
        }
    }

    view_close();
    return 0;
}