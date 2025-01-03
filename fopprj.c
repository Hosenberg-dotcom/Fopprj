#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void display_main_menu();
void new_user_menu();
void login_menu();
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
        "Create New User",
        "Login",
        "Exit"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;

    // Create a new window for the menu
    int box_start_y = rows / 8;
    int box_start_x = cols / 8;
    int box_height = 6 * rows / 8;
    int box_width = 6* cols / 8;
    WINDOW *menu_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(menu_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 0, (box_width - strlen("Main Menu")) / 2, "Main Menu");

    while (1) {
        // Print menu options with highlighting
        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                wattron(menu_win, A_REVERSE); // Highlight the selected option
            }
            mvwprintw(menu_win, 2 + i, 2, "%s", options[i]);
            if (i == highlight) {
                wattroff(menu_win, A_REVERSE);
            }
        }

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
                        new_user_menu();
                        return;
                    case 1:
                        delwin(menu_win);
                        login_menu();
                        return;
                    case 2:
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

void new_user_menu() {
    clear();
    mvprintw(2, 10, "=== Create New User ===");
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

void exit_game() {
    clear();
    mvprintw(2, 10, "Exiting the game. Goodbye!");
    refresh();
    getch();
}


