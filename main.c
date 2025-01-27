#include "headers.h"
int main() {
    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0); // Hide the cursor
    srand(time(NULL));

    // Display the main menu
    display_main_menu();

    // End ncurses mode
    endwin();
    return 0;
}