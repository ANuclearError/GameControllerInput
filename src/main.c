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
            char key = KEYBOARD[i][j];
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

    bool key_press = false;
    Uint32 key_press_ticks = SDL_GetTicks();

    int move_x = 0;
    int move_y = 0;
    Uint32 move_ticks = SDL_GetTicks();

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
                }
            }
        }
        refresh();
        if (key_press && (SDL_GetTicks() - key_press_ticks) > 100)
        {
            printf("Clearing\n");
            k_cursor.selected = -1;
            key_press = false;
            refresh();
        }
    }

    view_close();
    return 0;
}