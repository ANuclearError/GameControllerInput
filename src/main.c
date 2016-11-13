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
#include "keyboard.h"
#include "view.h"

int k_index = 0;

Cursor k_cursor = {0, 0, 3, -1};

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

void refresh()
{
    clear_render();
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            char key = KEYBOARDS[k_index].k_keys[i][j];
            int mode = get_mode(i, j);
            render_key(i, j, key, mode);
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
    SDL_Event e;
    while (run)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }
        }
        refresh();
        SDL_Delay(67);
    }

    view_close();
    return 0;
}