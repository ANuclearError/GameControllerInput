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
        if (x == (k_cursor.selected / k_cursor.size) &&
            y == (k_cursor.selected % k_cursor.size))
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
    int x = (k_cursor.selected / k_cursor.size);
    int y = (k_cursor.selected % k_cursor.size);
    return KEYBOARD[k_cursor.x + x][k_cursor.y + y];
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

    refresh();
    bool run = true;

    bool key_press = false;
    Uint32 key_press_ticks = SDL_GetTicks();

    // int move_x = 0;
    // int move_y = 0;
    // Uint32 move_ticks = SDL_GetTicks();

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
                SDL_Keycode key = e.key.keysym.sym;
                if (key >= SDLK_KP_1 && key <= SDLK_KP_9 && !key_press)
                {
                    key_press = true;
                    key_press_ticks = SDL_GetTicks();
                    k_cursor.selected = get_position(e.key.keysym.sym);
                    input[pos] = get_selected_key();
                    pos++;
                    printf("Input: %s\tPos: %d\n", input, pos);
                }
                else if (key == SDLK_BACKSPACE)
                {
                    input[pos - 1] = '\0';
                    if (pos > 0)
                    {
                        pos--;
                    }
                    printf("Input: %s\tPos: %d\n", input, pos);
                }
                else if (key == SDLK_w)
                {
                    k_cursor.y = k_cursor.y - 1;
                    if (k_cursor.y < 0)
                    {
                        k_cursor.y = ROWS - k_cursor.size;
                    }
                }
                else if (key == SDLK_s)
                {
                    k_cursor.y = (k_cursor.y + 1) % (ROWS - k_cursor.size + 1);
                }
                else if (key == SDLK_a)
                {
                    k_cursor.x = k_cursor.x - 1;
                    if (k_cursor.x < 0)
                    {
                        k_cursor.x = COLS - k_cursor.size;
                    }
                }
                else if (key == SDLK_d)
                {
                    k_cursor.x = (k_cursor.x + 1) % (COLS - k_cursor.size + 1);
                }

            }
        }
        refresh();
        if (key_press && (SDL_GetTicks() - key_press_ticks) > 100)
        {
            k_cursor.selected = -1;
            key_press = false;
            refresh();
        }
    }

    view_close();
    return 0;
}