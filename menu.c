#include "headers.h"

this_game_setups this_game_settings = {100, 3, '@', "Guest\0"};

void display_main_menu() {
    clear();
    refresh();
    curs_set(0);
    int rows, cols;
    noecho();
    getmaxyx(stdscr, rows, cols);
   
    const char *options[] = {
        "Enter as a Guest",
        "Log in",
        "Sign in",
        "Score table",
        "Settings",
        "Exit"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;
    int dot_count = 0;

    // Create a new window for the menu
    int box_start_y = rows / 8;
    int box_start_x = cols / 8;
    int box_height = 6 * rows / 8;
    int box_width = 6 * cols / 8;
    WINDOW *menu_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(menu_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(menu_win, 0, 0);
    int title_x = (box_width - strlen(" The Rogue ")) / 2;
    mvwprintw(menu_win, 0, title_x, " The Rogue ");
    
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
    mvwprintw(menu_win, art2_start_y + 2, art2_start_x, "       @p~qp~~FOP");
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
    mvwprintw(menu_win, art2_start_y + 15, art2_start_x, "      `-'       `--' Wassup");



        // Highlight the current option
        mvwchgat(menu_win, 4 + highlight * 4, title_x, strlen(options[highlight]), A_REVERSE, 0, NULL);

        display_loading_bar(menu_win, box_width, dot_count);

        // Increment dot count
        dot_count = (dot_count + 1) % 13; // Reset after 12 dots
        napms(500);
        nodelay(menu_win, TRUE);
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
                        display_scoreboard(this_game_settings.player_name);
                        return;
                    case 4:
                        delwin(menu_win);
                        settings_menu();
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
    noecho();
    curs_set(0);
    refresh();
    //getch();
    display_game();
}

void login_menu() {
    curs_set(1);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    echo();
    int box_start_y = 2 * rows / 8;
    int box_start_x = 1 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 3 * cols / 4;
    int valid_input = 0;
    char username[30];
    char password[30];
    WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
        keypad(settings_win, TRUE);

        // Draw the box
        box(settings_win, 0, 0);
        int title_x = (box_width - strlen("# loging in #")) / 2;
        mvwprintw(settings_win, 0, title_x, "# loging in #");
        mvwprintw(settings_win, 3, 2, "Enter Username: ");
        mvwprintw(settings_win, 6, 2, "Enter Password: ");
        wrefresh(settings_win);
        mvwgetnstr(settings_win, 3, 2 + strlen("Enter Username: "), username, 29);
        mvwgetnstr(settings_win, 6, 2 + strlen("Enter Password: "), password, 29);

        FILE *file = fopen("usersInputs.txt", "r");
        if (file == NULL) {
            clear();
            noecho();
            mvprintw(rows / 2, cols / 2, "Error: Could not open file!");
            mvprintw(rows / 2 + 2, cols / 2, "Press any key to return to the previous menu...");
            refresh();
            getch();
            curs_set(0);
            display_main_menu();
            return;
        }
        int duplicate_found = 0;
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char stored_username[30], stored_password[50];
            sscanf(line, "%29s %29s %*s", stored_username, stored_password);
            if ((strcmp(username, stored_username) == 0) && (strcmp(password, stored_password) == 0)) {
                duplicate_found = 1;
                strcpy(this_game_settings.player_name, stored_username);
                break;
            }
        }
        fclose(file);
        if(duplicate_found)
        {
            mvwprintw(settings_win, 12, 2, "Wellcome to the game %s", username);
            mvwprintw(settings_win, 13, 2, "please press 1 if you wnat to start a new game or 2 to reload a saved game");
            wrefresh(settings_win);
            char a;
            while(1)
            {
                curs_set(0);
                noecho();
                a = getch();
                if(a == '1')
                {
                    clear();
                    curs_set(0);
                    noecho();
                    delwin(settings_win);
                    refresh();
                    display_game();
                }
                else if(a == '2')
                {
                    clear();
                    curs_set(0);
                    noecho();
                    delwin(settings_win);
                    refresh();
                    if (does_save_exist()) {
                        resume_game();
                    } else {
                        printw("No save file found for user: %s\n", this_game_settings.player_name);
                    }
                }
            }
        }
        else
        {
            mvwprintw(settings_win, 12, 2, "your username or password did not found");
            mvwprintw(settings_win, 13, 2, "press any key to return to the main menu");
            wrefresh(settings_win);
            getch();
            clear();
            curs_set(0);
            noecho();
            refresh();
            display_main_menu();
            return;
            getch();
            clear();
            curs_set(0);
            noecho();
            refresh();
            display_main_menu();
            return;
        }

}

void sign_in_menu() {
    curs_set(1);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    echo();
    int box_start_y = 2 * rows / 8;
    int box_start_x = 1 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 3 * cols / 4;
    int valid_input = 0;
    char username[30];
    char password[30];
    char email[50];

    while (!valid_input) {
        clear();
        refresh();
        WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
        keypad(settings_win, TRUE);

        // Draw the box
        box(settings_win, 0, 0);
        int title_x = (box_width - strlen("# Create new account #")) / 2;
        mvwprintw(settings_win, 0, title_x, "# Create new account #");
        mvwprintw(settings_win, 3, 2, "Enter Username: ");
        mvwprintw(settings_win, 6, 2, "Enter Password: ");
        mvwprintw(settings_win, 9, 2, "Enter Email: ");
        wrefresh(settings_win);
        mvwgetnstr(settings_win, 3, 2 + strlen("Enter Username: "), username, 29);
        mvwgetnstr(settings_win, 6, 2 + strlen("Enter Password: "), password, 29);
        mvwgetnstr(settings_win, 9, 2 + strlen("Enter Email: "), email, 49);

        FILE *file = fopen("usersInputs.txt", "r");
        if (file == NULL) {
            clear();
            noecho();
            mvprintw(rows / 2, cols / 2, "Error: Could not open file!");
            mvprintw(rows / 2 + 2, cols / 2, "Press any key to return to the previous menu...");
            refresh();
            getch();
            curs_set(0);
            display_main_menu();
            return;
        }

        char line[100];
        int duplicate_found = 0;
        while (fgets(line, sizeof(line), file)) {
            char stored_username[30], stored_email[50];
            sscanf(line, "%29s %*s %49s", stored_username, stored_email);
            if (strcmp(username, stored_username) == 0) {
                mvwprintw(settings_win, 12, 2, "Error: Username already exists!");
                wrefresh(settings_win);
                duplicate_found = 1;
                break;
            }
            if (strcmp(email, stored_email) == 0) {
                mvwprintw(settings_win, 12, 2, "Error: Email already exists!");
                wrefresh(settings_win);
                duplicate_found = 1;
                break;
            }
        }
        fclose(file);

        if (duplicate_found) {
            mvwprintw(settings_win, 15, 2, "Press any key to re-enter details...");
            wrefresh(settings_win);
            getch();
            continue;
        }

        if (strlen(password) < 7 || !strpbrk(password, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") ||
            !strpbrk(password, "abcdefghijklmnopqrstuvwxyz") || !strpbrk(password, "0123456789") ||
            !strpbrk(password, "!@#$%^&*()-_+=")) {
            mvwprintw(settings_win, 12, 2, "Error: Password must be at least 7 characters long!");
            mvwprintw(settings_win, 13, 2, "Include uppercase, lowercase, number, and special character.");
            mvwprintw(settings_win, 15, 2, "Press any key to re-enter details...");
            wrefresh(settings_win);
            getch();
            continue;
        }

        if (!regex_match(email, "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$")) {
            mvwprintw(settings_win, 12, 2, "Error: Invalid email format!");
            mvwprintw(settings_win, 15, 2, "Press any key to re-enter details...");
            wrefresh(settings_win);
            getch();
            continue;
        }

        valid_input = 1;
    }

    FILE *file = fopen("usersInputs.txt", "a+");
    if (file != NULL) {
        fprintf(file, "%s %s %s\n", username, password, email);
        fclose(file);
    }
    mvprintw(12 + box_start_y, 2 + box_start_x, "User created successfully!");
    mvprintw(15 + box_start_y, 2 + box_start_x, "Press any key to return to the main menu...");
    refresh();
    getch();
    curs_set(0);
    noecho();
    clear();
    refresh();
    display_main_menu();
}


void score_table_menu() {
    clear();
    mvprintw(2, 10, "=== Score Table ===");
    mvprintw(4, 10, "This feature is under construction.");
    mvprintw(6, 10, "Press any key to return to the main menu.");
    refresh();
    getch();
}

void settings_menu() {
    curs_set(0);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *options[] = {
        "Set Difficulty",
        "Change Character Color",
        "Choose Hero",
        "Select Music",
        "Profile",
        "Back to Main Menu"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; 
    int choice;

    int box_start_y = 2 * rows / 8;
    int box_start_x = 3 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 1 * cols / 4;
    WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(settings_win, TRUE); 

    box(settings_win, 0, 0);
    int title_x = (box_width - strlen(" #Settings# ")) / 2;
    mvwprintw(settings_win, 0, title_x, "# Settings #");

    while (1) {
        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                wattron(settings_win, A_REVERSE);
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
                wattroff(settings_win, A_REVERSE);
            } else {
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
            }
        }

        wrefresh(settings_win);
        choice = wgetch(settings_win);
        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % n_options;
                break;
            case '\n':
                switch (highlight) {
                    case 0:
                        delwin(settings_win);
                        set_difficulty();
                        return;
                    case 1:
                        delwin(settings_win);
                        change_character_color();
                        return;
                    case 2:
                        delwin(settings_win);
                        choose_hero();
                        return;
                    case 3:
                        delwin(settings_win);
                        select_music();
                        return;
                    case 4:
                        delwin(settings_win);
                        display_profile();
                        return;
                    case 5:
                        delwin(settings_win);
                        display_main_menu();
                        return;
                }
                break;
            default:
                break;
        }
    }

    delwin(settings_win);
}



void set_difficulty() {
    curs_set(0);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *options[] = {
        "Easy",
        "Medium",
        "Hard",
        "Rough",
        "Back to Main Menu"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;

    // Create a new window for the settings menu
    int box_start_y = 2 * rows / 8;
    int box_start_x = 3 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 1 * cols / 4;
    WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(settings_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(settings_win, 0, 0);
    int title_x = (box_width - strlen(" #Settings# ")) / 2;
    mvwprintw(settings_win, 0, title_x, "# Settings #");

    while (1) {
        // Print menu options with highlighting
        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                wattron(settings_win, A_REVERSE);
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
                wattroff(settings_win, A_REVERSE);
            } else {
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
            }
        }

        // Refresh the window
        wrefresh(settings_win);

        // Handle user input
        choice = wgetch(settings_win);
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
                        this_game_settings.difficulty = 100;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 1:
                        this_game_settings.difficulty = 80;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 2:
                        this_game_settings.difficulty = 60;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 3:
                        this_game_settings.difficulty = 40;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 4:
                        delwin(settings_win);
                        refresh();
                        display_main_menu();
                        return;
                }
                break;
            default:
                break;
        }
    }

    // Delete the window at the end
    delwin(settings_win);
}

void change_character_color() {
    curs_set(0);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *options[] = {
        "Red",
        "Blue",
        "Green",
        "Yellow",
        "Back to Main Menu"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;

    // Create a new window for the settings menu
    int box_start_y = 2 * rows / 8;
    int box_start_x = 3 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 1 * cols / 4;
    WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(settings_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(settings_win, 0, 0);
    int title_x = (box_width - strlen(" #Settings# ")) / 2;
    mvwprintw(settings_win, 0, title_x, "# Settings #");

    while (1) {
        // Print menu options with highlighting
        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                wattron(settings_win, A_REVERSE);
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
                wattroff(settings_win, A_REVERSE);
            } else {
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
            }
        }

        // Refresh the window
        wrefresh(settings_win);

        // Handle user input
        choice = wgetch(settings_win);
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
                        this_game_settings.hero_color = 1;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 1:
                        this_game_settings.hero_color = 3;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 2:
                        this_game_settings.hero_color = 2;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 3:
                        this_game_settings.hero_color = 4;
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 4:
                        delwin(settings_win);
                        refresh();
                        display_main_menu();
                        return;
                }
                break;
            default:
                break;
        }
    }

    // Delete the window at the end
    delwin(settings_win);
}

void select_music() {
    curs_set(0);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *options[] = {
        "Track1.mp3",
        "Track2.mp3",
        "Track3.mp3",
        "Mute",
        "Back to Main Menu"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;

    // Create a new window for the settings menu
    int box_start_y = 2 * rows / 8;
    int box_start_x = 3 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 1 * cols / 4;
    WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(settings_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(settings_win, 0, 0);
    int title_x = (box_width - strlen(" #Settings# ")) / 2;
    mvwprintw(settings_win, 0, title_x, "# Settings #");

    while (1) {
        // Print menu options with highlighting
        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                wattron(settings_win, A_REVERSE);
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
                wattroff(settings_win, A_REVERSE);
            } else {
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
            }
        }

        // Refresh the window
        wrefresh(settings_win);

        // Handle user input
        choice = wgetch(settings_win);
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
                        start_music(options[0]);
                        delwin(settings_win);
                        select_music();
                        return;
                    case 1:
                        start_music(options[1]);
                        delwin(settings_win);
                        select_music();
                        return;
                    case 2:
                        start_music(options[2]);
                        delwin(settings_win);
                        select_music();
                        return;
                    case 3:
                        delwin(settings_win);
                        stop_music();
                        select_music();
                        return;
                    case 4:
                        delwin(settings_win);
                        refresh();
                        display_main_menu();
                        return;
                }
                break;
            default:
                break;
        }
    }

    // Delete the window at the end
    delwin(settings_win);
}

void choose_hero() {
    curs_set(0);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    const char *options[] = {
        "Zakani(@)",
        "Jalili(&)",
        "Poormahammadi($)",
        "Dr.Pezeshkian(%)",
        "Back to Main Menu"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;

    // Create a new window for the settings menu
    int box_start_y = 2 * rows / 8;
    int box_start_x = 3 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 1 * cols / 4;
    WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(settings_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(settings_win, 0, 0);
    int title_x = (box_width - strlen(" #Settings# ")) / 2;
    mvwprintw(settings_win, 0, title_x, "# Settings #");

    while (1) {
        // Print menu options with highlighting
        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                wattron(settings_win, A_REVERSE);
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
                wattroff(settings_win, A_REVERSE);
            } else {
                mvwprintw(settings_win, 4 + i * 3, (box_width - strlen(options[i])) / 2, "%s", options[i]);
            }
        }

        // Refresh the window
        wrefresh(settings_win);

        // Handle user input
        choice = wgetch(settings_win);
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
                        this_game_settings.hero_symbol = '@'; 
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 1:
                        this_game_settings.hero_symbol = '&';
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 2:
                        this_game_settings.hero_symbol = '$';
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 3:
                        this_game_settings.hero_symbol = '%';
                        delwin(settings_win);
                        settings_menu();
                        return;
                    case 4:
                        delwin(settings_win);
                        refresh();
                        display_main_menu();
                        return;
                }
                break;
            default:
                break;
        }
    }

    // Delete the window at the end
    delwin(settings_win);
}

void exit_game() {
    curs_set(0);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
     // Create a new window for the settings menu
    int box_start_y = 3 * rows / 8;
    int box_start_x = 2 * cols / 8;
    int box_height = 1 * rows / 4;
    int box_width = 1 * cols / 2;
    WINDOW *settings_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(settings_win, TRUE); // Enable keypad input for the window

    // Draw the box
    box(settings_win, 0, 0);
    int title_x = (box_width - strlen("Are you sure you want to leave?")) / 2;
    mvwprintw(settings_win, 1, title_x, "Are you sure you want to leave?");
    const char *options[] = {
        "Yes",
        "No",
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0; // Tracks the currently highlighted option
    int choice;
    while (1) {
        // Print menu options with highlighting
        for (int i = 0; i < n_options; i++) {
            if (i == highlight) {
                wattron(settings_win, A_REVERSE);
                mvwprintw(settings_win, 4 + i * 3, (box_width ) / 2, "%s", options[i]);
                wattroff(settings_win, A_REVERSE);
            } else {
                mvwprintw(settings_win, 4 + i * 3, (box_width) / 2, "%s", options[i]);
            }
        }
        // Refresh the window
        wrefresh(settings_win);

        // Handle user input
        choice = wgetch(settings_win);
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
                        close_all_ncurses_windows();
                        return;
                    case 1:
                        clear();
                        delwin(settings_win);
                        display_main_menu();
                        return;
                }
                break;
                default:
                break;
                 }
    }

    // Delete the window at the end
    delwin(settings_win);
    
}

void display_loading_bar(WINDOW *menu_win, int box_width, int dot_count) {
    noecho();
    const char *loading_text = "Loading"; // Base text for loading
    int loading_x = (box_width - (strlen(loading_text) + dot_count)) / 2; // Center text horizontally
    int loading_y = getmaxy(menu_win) - 3; // Position near the bottom of the window

    // Re-draw the left and right border
    mvwaddch(menu_win, loading_y, 0, ACS_VLINE); // Left border
    mvwaddch(menu_win, loading_y, box_width - 1, ACS_VLINE); // Right border

    // Create the loading text with dots
    char loading_with_dots[20];
    snprintf(loading_with_dots, sizeof(loading_with_dots), "%s%s", loading_text, "............." + (12 - dot_count));

    // Clear only the middle part where loading text is displayed
    mvwprintw(menu_win, loading_y, 1, "%-*s", box_width - 2, ""); // Clear the line except borders

    // Print the loading text
    mvwprintw(menu_win, loading_y, loading_x, "%s", loading_with_dots); // Print loading text
    wrefresh(menu_win); // Refresh the window to display changes
}

int regex_match(const char *string, const char *pattern) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0; // Regex compilation failed
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    return ret == 0;
}

void close_all_ncurses_windows() {
    endwin();  
    printf("\033c"); 
}

void load_scoreboard(Player players[], int *player_count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printw("Error opening scoreboard file.\n");
        return;
    }

    *player_count = 0;
    while (fscanf(file, "%s %d %d %d", players[*player_count].username, 
                  &players[*player_count].gold, 
                  &players[*player_count].score, 
                  &players[*player_count].games_played) == 4) {
        (*player_count)++;
    }
    fclose(file);
}

int compare_scores(const void *a, const void *b) {
    return ((Player *)b)->score - ((Player *)a)->score;
}

void display_scoreboard(const char *current_user) {
    clear();
    refresh();
    curs_set(0);
    if(strcmp(current_user, "Guest") == 0)
    {
        mvprintw(10, 60, "You need to login to see scoretable");
        getch();
        clear();
        display_main_menu();
        return;
    }
    Player players[MAX_PLAYERS];
    int player_count = 0;
    load_scoreboard(players, &player_count, "scoreboard.txt");

    qsort(players, player_count, sizeof(Player), compare_scores);

    int start = 0, ch;
    int max_rows, max_cols;
    getmaxyx(stdscr, max_rows, max_cols);
    int selected = 0;

    WINDOW *score_win = newwin(max_rows * 3 / 5, max_cols / 2, max_rows * 1 / 5, max_cols / 4);
    keypad(score_win, TRUE);
    
    while (1) {
        werase(score_win);
        box(score_win, 0, 0);
        mvwprintw(score_win, 0, (max_cols / 2 - strlen("🏆 Scoreboard 🏆")) / 2, "🏆 Scoreboard 🏆");

        for (int i = start, row = 3; i < player_count && row < max_rows - 2; i++, row++) {
            int color = (i == 0) ? 1 : (i == 1) ? 1 : (i == 2) ? 1 : 3;
            if (strcmp(players[i].username, current_user) == 0) color = 2;
            if (i == selected) color = 4;

            wattron(score_win, COLOR_PAIR(color));
            if (i < 3) wattron(score_win, A_UNDERLINE);

            mvwprintw(score_win, row, 2, "%2d. %-15s Gold: %d | Score: %d | Games: %d", 
                      i + 1, players[i].username, players[i].gold, players[i].score, players[i].games_played);

            wattroff(score_win, A_UNDERLINE);
            wattroff(score_win, COLOR_PAIR(color));

            if (i == 0) mvwprintw(score_win, row, max_cols / 4 + 15, "🏆 CHAMPION");
            if (i == 1) mvwprintw(score_win, row, max_cols / 4 + 15, "🥈 Runner-up");
            if (i == 2) mvwprintw(score_win, row, max_cols / 4 + 15, "🥉 Third Place");
        }
        
        wrefresh(score_win);
        ch = wgetch(score_win);

        if (ch == 'q')
    {
        delwin(score_win);
        refresh();
        display_main_menu();
        return;

    }
        if (ch == KEY_UP && selected > 0) selected--;
        if (ch == KEY_DOWN && selected < player_count - 1) selected++;
    }
}

void display_profile() {
    curs_set(0);
    clear();
    refresh();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int box_start_y = 2 * rows / 8;
    int box_start_x = 3 * cols / 8;
    int box_height = 1 * rows / 2;
    int box_width = 1 * cols / 4;
    WINDOW *profile_win = newwin(box_height, box_width, box_start_y, box_start_x);
    keypad(profile_win, TRUE);

    box(profile_win, 0, 0);
    int title_x = (box_width - strlen("# Profile #")) / 2;
    mvwprintw(profile_win, 0, title_x, "# Profile #");
    char line[256];
    char username[50], password[50], email[100];
    int found = 0;

    if(strcmp(this_game_settings.player_name, "Guest") == 0)
    {
        mvwprintw(profile_win, 3, 2, "Guest user");
        wrefresh(profile_win);

        getch();
        return;
    }
    
    FILE *file = fopen("usersinputs.txt", "r");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "%49s %49s %99s", username, password, email) == 3) {
                if (strcmp(username, this_game_settings.player_name) == 0) {
                    found = 1;
                    break;
                }
            }
        }
        fclose(file);
    }
    if (found) {
        mvwprintw(profile_win, 3, 2, "Username:");
        mvwprintw(profile_win, 5, 2, "%s", username);
        mvwprintw(profile_win, 7, 2, "Email:");
        mvwprintw(profile_win, 9, 2, "%s", email);
        mvwprintw(profile_win, 11, 2, "Password:");
        mvwprintw(profile_win, 13, 2, "%s", password);
    } else {
        mvwprintw(profile_win, 3, 2, "User Not Found!");
    }
    wrefresh(profile_win);
    while (1) {
        int ch = wgetch(profile_win);
        if (ch == 'q') {
            delwin(profile_win);
            settings_menu();
            return;
        }
    }
}
