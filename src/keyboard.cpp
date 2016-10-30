#include <SDL.h>
#include <iostream>

using namespace std;

/**
 * The controller being used to handle text input from the user.
 */ 
SDL_GameController* controller = NULL;

/**
 * #include <SDL.h>
 *
 * Initialises the keyboard, ensuring that the controller is connected and
 * available.
 *
 * Bit messy due to the need to iterate through all potential connected devices.
 */
bool keyboard_init()
{    
    cout << "Beginning controller initialisation.\n";
    cout << SDL_NumJoysticks() << " controllers/joysticks found\n";
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            cout << "Controller found\n";
            controller = SDL_GameControllerOpen(i);
            if (controller)
            {
                return true;
            }
            else
            {
                cout << "SDL_Error controller: " << SDL_GetError() << "\n";
                return false;
            }
        }
        else {
            cout << i << " is not a compatible controller.\n";
        }
    }

    if (controller == NULL)
    {
        cout << "SDL_Error controller: " << SDL_GetError() << "\n";
        return false;
    }
    cout << "Controller initialisation successful.\n";
    return true;
}

/**
 * #include <SDL.h>
 *
 * Handles the disconnection of the controller.
 */
void keyboard_close()
{
    SDL_GameControllerClose(controller);
    controller = NULL;
}