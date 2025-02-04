#include "headers.h"
int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));
    display_main_menu();
    stop_music();
    endwin();
    return 0;
}