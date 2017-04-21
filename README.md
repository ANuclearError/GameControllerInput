# GameControllerInput
## Synopsis
A prototype of a novel method of text input utilising game controllers. The
text input revolves around the use of the right control stick to select from a
grid of characters within the keyboard.

## Author
Aidan O'Grady (201218150) - wlb12153@uni.strath.ac.uk

## Motivation
This project is a submission for the main assignment of class CS548 Designing
Usable Systems for the MEng Computer Science course at the University of
Strathclyde, Glasgow.

## Compiling
The program uses the Mingw GCC compiler on Windows. Other compilers have not
been tested with the prototype. To compile the program enter:

`mingw32-make`

## Running the prototype
Running the keyboard has two optional arguments to it: the size of the cursor
(from 1 to 3) and the benchmark flag ("--benchmark" or "-b"). To run the
keyboard from the command line (recommended) enter:

`.\keyboard [1 | 2 | 3] [-b]`

If the program is run without any arguments, it defaults to a cursor size of
three and without benchmarking being performed.

Please note, **you must have a controller connected to run the program**. The
program cannot run without it. If you do not have a controller available, please
e-mail me.
