#include <SDL.h>
#include <iostream>
#include "view.h"

/**
 * The window of the keyboard.
 */
SDL_Window* window = NULL;

/**
 * The renderer of the keyboard, rendering the current layout of the keyboard.
 */
SDL_Renderer* renderer = NULL;


/**
 * #include <SDL.h>
 * #include <iostream>
 *
 * Initializes the system.
 *
 * Uses the SDL library to create a window and renderer responsible for drawing
 * keyboard based on the dimensions defined in the header file.
 *
 * Returns true if successful, otherwise false.
 */
bool init()
{
    std::cout << "Beginning initialisation.\n";

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL_Error initialising: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("Keyboard",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIN_SIZE.w, WIN_SIZE.h,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        std::cout << "SDL_Error creating window: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "SDL_Error creating renderer: " << SDL_GetError() << "\n";
        return false;
    }

    std::cout << "Initialisation successful.\n";
    return true;
}

/**
 * #include <SDL.h>
 * #include <iostream>
 *
 * Renders the current state of the keyboard.
 */
void render_background()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, BKGRD.r, BKGRD.g, BKGRD.b, BKGRD.a);
    SDL_RenderFillRect(renderer, NULL);
}

/**
 * #include <SDL.h>
 *
 * Renders the key at the given coordinates.
 *
 * x the x coordinate of the key
 * y the y coordinate of the key
 */
void render_key(int x, int y)
{
    SDL_SetRenderDrawColor(renderer, KEY.r, KEY.g, KEY.b, KEY.a);
    SDL_Rect key = {
        GAP + ((KEY_SIZE.w + GAP) * y),
        GAP + ((KEY_SIZE.h + GAP) * x) + TEXT_BOX_HEIGHT,
        KEY_SIZE.w,
        KEY_SIZE.h
    };
    SDL_RenderFillRect(renderer, &key);
}

/**
 * Presents the current render to the window.
 */
void update()
{
    SDL_RenderPresent(renderer);
}

/**
 * #include <SDL.h>
 * #include <iostream>
 *
 * Graceful shutdown of the system.
 *
 * Shutdown everything created by SDL, ensuring that the shutdown is safe.
 */
void close()
{
    std::cout << "Beginning shutdown.\n";
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_Quit();
    std::cout << "Shutdown successful.\n";
}