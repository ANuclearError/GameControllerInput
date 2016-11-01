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
int pos = -1;

string input = "";

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

            // Draw keyboard.
            if (pos >= 0 && i == (y + pos / size) && j == (x + pos % size))
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

void joystick_event(SDL_ControllerAxisEvent* e)
{
    switch (e->axis)
    {
        case SDL_CONTROLLER_AXIS_LEFTX:
            cout << "Moving matrix left/right\n"; 
            break;       
        case SDL_CONTROLLER_AXIS_LEFTY:
            cout << "Moving matrix up/down\n";
            break;
        case SDL_CONTROLLER_AXIS_RIGHTX:
            cout << "Selecting character left/right\n";
            break;
        case SDL_CONTROLLER_AXIS_RIGHTY:
            cout << "Selecting character up/down\n";
            break;
        case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
            cout << "Left trigger\n";
        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
            cout << "Right trigger\n";
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

    Uint32 last = SDL_GetTicks();
    cout << "Start tick: " << last << "\n";
    while (run)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }
            else if (e.type == SDL_CONTROLLERAXISMOTION)
            {
                if (SDL_GetTicks() - last > 100) {
                    Sint16 val = e.caxis.value;
                    if (val > 8000 || val < - 8000) {
                        joystick_event(&e.caxis);
                        last = SDL_GetTicks();
                    }
                }
            }
        }
        SDL_Delay(67);
    }

    keyboard_close();
    view_close();
    return 0;
}