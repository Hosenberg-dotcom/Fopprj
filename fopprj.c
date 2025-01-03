#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void display_main_menu();
void guest_menu();
void login_menu();
void sign_in_menu();
void score_table_menu();
void music_menu();
void exit_game();

int main() {
    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0); // Hide the cursor

    // Display the main menu
    display_main_menu();

    // End ncurses mode
    endwin();
    return 0;
}

void display_main_menu() {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *options[] = {
        "Guest",
        "Log in",
        "Sign in",
        "Score table",
        "Music",
        "Exit"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;

    // Create a new window for the menu
    int box_start_y = rows / 8;
    int box_start_x = cols / 8;
    int box_height = 6 * rows / 8;
    int box_width = 6 * cols / 8;
    WINDOW *menu_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(menu_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(menu_win, 0, 0);
    int title_x = (box_width - strlen("Main Menu")) / 2;
    mvwprintw(menu_win, 0, title_x, "Main Menu");
    
    while (1) {
        // Print menu options with highlighting
        for (int i = 0; i < n_options; i++) {
            mvwprintw(menu_win, 4 + i * 4, title_x, "%s", options[i]);
        }
            // Print ASCII art inside the box, on the left
        int art1_start_y = 6; // Vertical position for ASCII art
        int art1_start_x = 4; // Horizontal position for ASCII art
        mvwprintw(menu_win, art1_start_y, art1_start_x, "       ___------__");
        mvwprintw(menu_win, art1_start_y + 1, art1_start_x, " |\\__-- /\\       _-");
        mvwprintw(menu_win, art1_start_y + 2, art1_start_x, " |/    __      -");
        mvwprintw(menu_win, art1_start_y + 3, art1_start_x, " //\\  /  \\    /__");
        mvwprintw(menu_win, art1_start_y + 4, art1_start_x, " |  o|  0|__     --_");
        mvwprintw(menu_win, art1_start_y + 5, art1_start_x, " \\\\____-- __ \\   ___-");
        mvwprintw(menu_win, art1_start_y + 6, art1_start_x, " (@@    __/  / /_");
        mvwprintw(menu_win, art1_start_y + 7, art1_start_x, "    -_____---   --_");
        mvwprintw(menu_win, art1_start_y + 8, art1_start_x, "     //  \\ \\\\   ___-");
        mvwprintw(menu_win, art1_start_y + 9, art1_start_x, "   //|\\__/  \\\\  \\");
        mvwprintw(menu_win, art1_start_y + 10, art1_start_x, "   \\_-\\_____/  \\-\\");
        mvwprintw(menu_win, art1_start_y + 11, art1_start_x, "        // \\\\--\\|   -Hey-");
        mvwprintw(menu_win, art1_start_y + 12, art1_start_x, "   ____//  ||_");
        mvwprintw(menu_win, art1_start_y + 13, art1_start_x, "  /_____\\ /___\\");
        mvwprintw(menu_win, art1_start_y + 14, art1_start_x, "______________________");
        // Print second ASCII art inside the box
    int art2_start_y = 6; // Vertical position for ASCII art 2
    int art2_start_x = (9 * box_width) / 12; // Horizontal position for ASCII art 2
    mvwprintw(menu_win, art2_start_y, art2_start_x, "         _nnnn_");
    mvwprintw(menu_win, art2_start_y + 1, art2_start_x, "        dGGGGMMb");
    mvwprintw(menu_win, art2_start_y + 2, art2_start_x, "       @p~qp~~qMb");
    mvwprintw(menu_win, art2_start_y + 3, art2_start_x, "       M|@||@) M|");
    mvwprintw(menu_win, art2_start_y + 4, art2_start_x, "       @,----.JM|");
    mvwprintw(menu_win, art2_start_y + 5, art2_start_x, "      JS^\\__/  qKL");
    mvwprintw(menu_win, art2_start_y + 6, art2_start_x, "     dZP        qKRb");
    mvwprintw(menu_win, art2_start_y + 7, art2_start_x, "    dZP          qKKb");
    mvwprintw(menu_win, art2_start_y + 8, art2_start_x, "   fZP            SMMb");
    mvwprintw(menu_win, art2_start_y + 9, art2_start_x, "   HZM            MMMM");
    mvwprintw(menu_win, art2_start_y + 10, art2_start_x, "   FqM            MMMM");
    mvwprintw(menu_win, art2_start_y + 11, art2_start_x, " __| \".        |\\dS\"qML");
    mvwprintw(menu_win, art2_start_y + 12, art2_start_x, " |    `.       | `' \\Zq");
    mvwprintw(menu_win, art2_start_y + 13, art2_start_x, " _)      \\.___.,|     .'");
    mvwprintw(menu_win, art2_start_y + 14, art2_start_x, " \\____   )MMMMMP|   .'");
    mvwprintw(menu_win, art2_start_y + 15, art2_start_x, "      `-'       `--' hjm");



        // Highlight the current option
        mvwchgat(menu_win, 4 + highlight * 4, title_x, strlen(options[highlight]), A_REVERSE, 0, NULL);

        // Refresh the window
        wrefresh(menu_win);

        // Handle user input
        choice = wgetch(menu_win);
        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % n_options;
                break;
            case '\n': // Enter key
                switch (highlight) {
                    case 0:
                        delwin(menu_win);
                        guest_menu();
                        return;
                    case 1:
                        delwin(menu_win);
                        login_menu();
                        return;
                    case 2:
                        delwin(menu_win);
                        sign_in_menu();
                        return;
                    case 3:
                        delwin(menu_win);
                        score_table_menu();
                        return;
                    case 4:
                        delwin(menu_win);
                        music_menu();
                        return;
                    case 5:
                        delwin(menu_win);
                        exit_game();
                        return;
                }
                break;
            default:
                break;
        }
    }

    // Delete the window at the end
    delwin(menu_win);
}

void guest_menu() {
    clear();
    mvprintw(2, 10, "=== Guest Mode ===");
    mvprintw(4, 10, "This feature is under construction.");
    mvprintw(6, 10, "Press any key to return to the main menu.");
    refresh();
    getch();
}

void login_menu() {
    clear();
    mvprintw(2, 10, "=== Login ===");
    mvprintw(4, 10, "This feature is under construction.");
    mvprintw(6, 10, "Press any key to return to the main menu.");
    refresh();
    getch();
}

void sign_in_menu() {
    clear();
    mvprintw(2, 10, "=== Sign In ===");
    mvprintw(4, 10, "This feature is under construction.");
    mvprintw(6, 10, "Press any key to return to the main menu.");
    refresh();
    getch();
}

void score_table_menu() {
    clear();
    mvprintw(2, 10, "=== Score Table ===");
    mvprintw(4, 10, "This feature is under construction.");
    mvprintw(6, 10, "Press any key to return to the main menu.");
    refresh();
    getch();
}

void music_menu() {
    clear();
    mvprintw(2, 10, "=== Music Menu ===");
    mvprintw(4, 10, "This feature is under construction.");
    mvprintw(6, 10, "Press any key to return to the main menu.");
    refresh();
    getch();
}

void exit_game() {
    clear();
    mvprintw(2, 10, "Exiting the game. Goodbye!");
    refresh();
    getch();
}