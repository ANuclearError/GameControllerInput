#ifndef KEYBOARD_H
#define KEYBOARD_H

/**
 * The number of rows in a keyboard.
 */
const int ROWS = 4;

/**
 * The number of columns in a keyboard.
 */
const int COLUMNS = 10;

/**
 * The different modes a keyboard can be in.
 */
enum Mode {lower, upper};

/**
 * A keyboard is defined by its mode and the characters it contains for this
 * mode.
 */
struct Keyboard {
    Mode mode;
    char keyboard[ROWS][COLUMNS];
};

/**
 * The keyboard mode for lower case characters, numbers and basic punctuation.
 */
const struct Keyboard LOWER = {
    lower,
    {
        {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
        {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
        {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\''},
        {'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '?'}
    }
};

/**
 * The keyboard mode for upper case characters, numbers and basic punctuation.
 */
const struct Keyboard UPPER = {
    upper,
    {
        {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
        {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
        {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '\''},
        {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '?'}
    }
};

#endif // KEYBOARD_H