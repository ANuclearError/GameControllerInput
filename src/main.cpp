#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "view.h"
#include "keyboard.h"

using namespace std;

const int JOYSTICK_DEAD_ZONE = 16000;

int x;
int y;
int size;

/**
 * Refreshes the display, calling the view functions to render the keys, while
 * handling the logic of how the key is to be rendered.
 */
void refresh()
{
    render_background();
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            string s(1, UPPER.keyboard[i][j]);

            if (i >= y && i < y + size && j >= x && j < x + size)
            {
                render_key(i, j, s.c_str(), HOVER);
            }
            else {
                render_key(i, j, s.c_str(), STANDARD);
            }
        }
    }
    update();
}

void joystick_event(SDL_Event* e)
{
    bool update = false;
    switch (e->caxis.axis)
    {
        case SDL_CONTROLLER_AXIS_LEFTX:
            if (e->caxis.value < -JOYSTICK_DEAD_ZONE)
            {
                x = (x - 1);
                if (x < 0)
                {
                    x = COLUMNS - size;
                }
                update = true;
            }
            else if (e->caxis.value > JOYSTICK_DEAD_ZONE)
            {
                x = (x + 1) % (COLUMNS - size + 1);
                update = true;
            }
            break;
        case SDL_CONTROLLER_AXIS_LEFTY:
            if (e->caxis.value < -JOYSTICK_DEAD_ZONE)
            {
                y = (y - 1);
                if (y < 0)
                {
                    y = ROWS - size;
                }
                update = true;
            }
            else if (e->caxis.value > JOYSTICK_DEAD_ZONE)
            {
                y = (y + 1) % (ROWS - size + 1);
                update = true;
            }
            break;
    }

    if (update) // Only want to redraw if necessary.
    {
        refresh();
    }
}

void handle_event(SDL_Event* e)
{
    switch (e->type)
    {
        case SDL_CONTROLLERBUTTONUP:
            cout << "Button up\n";
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            cout << "Button down\n";
            break;
        case SDL_CONTROLLERAXISMOTION:
            joystick_event(e);
            break;
    }
}

/**
 * #include <SDL.h>
 * #include <iostream>
 *
 * The main control loop of the system, handling events etc.
 */
int main(int argc, char* args[])
{
    x = 0;
    y = 0;
    size = 3;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "SDL_Error initialising: " << SDL_GetError() << "\n";
        return -1;
    }

    if (!(view_init() && keyboard_init()))
    {
        cout << "Failed to initialize.\n";
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
            else
            {
                handle_event(&e);
            }
        }
        SDL_Delay(67);
    }

    keyboard_close();
    view_close();
    return 0;
}