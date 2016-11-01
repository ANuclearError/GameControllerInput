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
int pos = 0;

string input = "Hello1";

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

            if (i == (y + pos / size) && j == (x + pos % size))
            {
                render_key(i, j, s.c_str(), ENTERED);
            }
            else if (i >= y && i < y + size && j >= x && j < x + size)
            {
                render_key(i, j, s.c_str(), HOVER);
            }
            else {
                render_key(i, j, s.c_str(), STANDARD);
            }
        }
    }
    render_input(input.c_str());
    update();
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
        }
        SDL_Delay(67);
    }

    keyboard_close();
    view_close();
    return 0;
}