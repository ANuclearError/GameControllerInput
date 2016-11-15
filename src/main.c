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
char input[128];

/**
 * The position where text is being entered.
 */
int pos = 0;

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
    render_input(input);
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
 * Prints the current matrix that is being hovered over by the cursor.
 */
void print_matrix()
{
    for (int i = 0; i < k_cursor.size; ++i)
    {
        printf("\t");
        for (int j = 0; j < k_cursor.size; ++j)
        {
            printf("%c ", KEYBOARD[k_cursor.y + i][k_cursor.x + j]);
        }
        printf("\n");
    }
    printf("\n");
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

    bool move = false;
    bool select = false;
    Uint32 last_move = SDL_GetTicks();
    Uint32 last_select = SDL_GetTicks();

    print_matrix();
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
                        input[pos] = get_selected_key();
                        pos++;
                        printf("Input: %s\n", input);
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
                    printf("Input: %s\n", input);
                    break;
                    case COMMAND_BACKSPACE:
                    pos = (pos - 1 > 0) ? pos - 1 : 0;
                    input[pos] = '\0';
                    printf("Input: %s\n", input);
                    break;
                    default:
                    break;
                }

            }
        }
        refresh();
        if (move && (SDL_GetTicks() - last_move) > 100)
        {
            move = false;
            print_matrix();
        }
        else if (select && (SDL_GetTicks() - last_select) > 100)
        {
            select = false;
            k_cursor.key = -1;
            refresh();
        }
    }

    view_close();
    return 0;
}