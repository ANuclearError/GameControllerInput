#ifndef VIEW_H
#define VIEW_H

/**
 * Structure for holding pixel dimensions of various on-screen objects. Each
 * size contains a width and height.
 */
struct Size
{
    int w;
    int h;
};

/**
 * The pixel gap between keys.
 */
const int GAP = 5;

/**
 * The gap required for the text box.
 */
const int TEXT_BOX_HEIGHT = 100;

/**
 * The size of the main window.
 */
const struct Size WIN_SIZE = {1555, 525};

/**
 * The responsive size of keys in pixels.
 */
const struct Size KEY_SIZE = {150, 100};

/**
 * The background colour of the keyboard.
 */
const SDL_Color BKGRD = {255, 255, 255, SDL_ALPHA_OPAQUE};

/**
 * The standard colour of keys.
 */
const SDL_Color STANDARD = {225, 225, 225, SDL_ALPHA_OPAQUE};

/**
 * The colour of keys that are being hovered over.
 */
const SDL_Color HOVER = {150, 150, 150, SDL_ALPHA_OPAQUE};

/**
 * The colour of keys that are being clicked on.
 */
const SDL_Color ENTERED = {75, 75, 75, SDL_ALPHA_OPAQUE};

/**
 * The colour of the characters being rendered.
 */
const SDL_Color CHAR_COL = {0, 0, 0, SDL_ALPHA_OPAQUE};

/**
 * The window of the keyboard.
 */
extern SDL_Window* window;

/**
 * The renderer of the keyboard, rendering the current layout of the keyboard.
 */
extern SDL_Renderer* renderer;

/**
 * The font used to render characters.
 */
extern TTF_Font* font;

/**
 * Initializes the system.
 *
 * Returns true if successful, otherwise false.
 */
bool view_init();

/**
 * Renders the given keyboard to the screen.
 */
void render_background();

/**
 * Renders the key at the given coordinates.
 */ 
void render_key(int x, int y, const char* c, SDL_Color color);

/**
 * Displays the string the user wishes to input.
 */
void render_input(const char* text);

/**
 * Presents the current render to the window.
 */
void update();

/**
 * Performs a graceful shutdown of the system.
 */
void view_close();

#endif // VIEW_H