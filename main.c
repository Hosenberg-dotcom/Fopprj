#include "headers.h"
int main() {
    setlocale(LC_ALL, "");
    // Initialize ncurses
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0); // Hide the cursor
    srand(time(NULL));

    // Display the main menu
    display_main_menu();

    // End ncurses mode
    //void exit_game();
    stop_music();
    endwin();
    return 0;
}