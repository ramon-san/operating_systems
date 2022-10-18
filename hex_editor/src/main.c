#include "interface.h"

int main(int argc, char const *argv[]) {
	initscr(); // Make standard screen (stdscr) for ncurses.
    cbreak();

    /* File is given as a parameter. */
    if (argc != 2) {
        printf("Using %s <file> \n", argv[0]);
        return(-1);
    }

    edit((char *)argv[1]);

    endwin(); // Frees memory from screen and closes ncurses.
    
    return 0;
}