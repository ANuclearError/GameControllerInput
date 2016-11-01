#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "view.h"

using namespace std;

/**
 * The window of the keyboard.
 */
SDL_Window* window = NULL;

/**
 * The renderer of the keyboard, rendering the current layout of the keyboard.
 */
SDL_Renderer* renderer = NULL;

/**
 * The font for rendering characters.
 */
TTF_Font* font = NULL;

/**
 * The rectangle containing the character 
 */
SDL_Rect char_rect;

/**
 * The rectangle for drawing the keys background.
 */
SDL_Rect key_rect;

/**
 * The area where the input text is added.
 */
SDL_Rect input_rect;

/**
 * Pointer to the surface used to draw a character to the screen.
 */
SDL_Surface* surface = NULL;

/**
 * Pointer to the texture used to draw a character to screen.
 */
SDL_Texture* texture = NULL;

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
bool view_init()
{
    cout << "Beginning view initialisation.\n";
    if (TTF_Init() == -1)
    {
        cout << "TTF_Error initialising: " << TTF_GetError() << "\n";
        return false;
    }

    font = TTF_OpenFont("arial.ttf", 72);
    if (font == NULL)
    {
        cout << "TTF_Error opening font: " << TTF_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("Keyboard",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIN_SIZE.w, WIN_SIZE.h,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        cout << "SDL_Error creating window: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cout << "SDL_Error creating renderer: " << SDL_GetError() << "\n";
        return false;
    }

    cout << "View initialisation successful.\n";
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
void render_key(int x, int y, const char* c, SDL_Color color)
{
    // Draw the background
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    key_rect = {
        GAP + ((KEY_SIZE.w + GAP) * y),
        GAP + ((KEY_SIZE.h + GAP) * x) + TEXT_BOX_HEIGHT,
        KEY_SIZE.w,
        KEY_SIZE.h
    };
    SDL_RenderFillRect(renderer, &key_rect);

    // Render the character
    surface = TTF_RenderText_Blended(font, c, CHAR_COL);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &char_rect.w, &char_rect.h);
    char_rect.x = key_rect.x + (key_rect.w / 2) - (char_rect.w / 2);
    char_rect.y = key_rect.y + (key_rect.h / 2) - (char_rect.h / 2);
    SDL_RenderCopy(renderer, texture, NULL, &char_rect);

    // Now need to ensure we aren't eating 2 gigs of RAM.
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = NULL;
    texture = NULL;
}

void render_input(const char* text)
{
    surface = TTF_RenderText_Blended(font, text, CHAR_COL);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &input_rect.w, &input_rect.h);
    input_rect.x = 50;
    input_rect.y = (TEXT_BOX_HEIGHT / 2) - (input_rect.h / 2);
    SDL_RenderCopy(renderer, texture, NULL, &input_rect);
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
void view_close()
{
    cout << "Beginning shutdown.\n";
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    TTF_Quit();
    SDL_Quit();
    cout << "Shutdown successful.\n";
}