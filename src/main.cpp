#include <SDL.h>
#include <iostream>
#include "view.h"
#include "keyboard.h"

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
            render_key(i, j);
        }
    }
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
    if (!init())
    {
        std::cout << "Failed to initialize.\n";
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
    }
    close();
    return 0;
}