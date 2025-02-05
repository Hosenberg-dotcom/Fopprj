#include "headers.h"

int save_game(Game* main_game, int level) {
    if (strcmp(this_game_settings.player_name, "Guest") == 0) {
        return 1;
    }
    char filename[50];
    snprintf(filename, sizeof(filename), "savegame_%s.dat", this_game_settings.player_name);
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 2;
    }

    fwrite(&level, sizeof(int), 1, file);  
    fwrite(&(main_game->hero), sizeof(Character), 1, file);  
    
    for (int i = 0; i < MAX_FLOORS; i++) {
        fwrite(&(main_game->floors[i]), sizeof(Floor), 1, file);  
        
        for (int y = 0; y < main_game->floors[i].height; y++) {
            fwrite(main_game->floors[i].map[y], sizeof(char), main_game->floors[i].width, file);
        }
    }

    fclose(file);
    return 0;
}


int load_game(Game* main_game, int* level) {
    if (strcmp(this_game_settings.player_name, "Guest") == 0) {
        return 1;
    }
    char filename[50];
    snprintf(filename, sizeof(filename), "savegame_%s.dat", this_game_settings.player_name);
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return 2;
    }
    fread(level, sizeof(int), 1, file);

    fread(&(main_game->hero), sizeof(Character), 1, file);

    for (int i = 0; i < MAX_FLOORS; i++) {
        fread(&(main_game->floors[i]), sizeof(Floor), 1, file);

        main_game->floors[i].map = (char**)malloc(main_game->floors[i].height * sizeof(char*));
        for (int y = 0; y < main_game->floors[i].height; y++) {
            main_game->floors[i].map[y] = (char*)malloc(main_game->floors[i].width * sizeof(char));
            fread(main_game->floors[i].map[y], sizeof(char), main_game->floors[i].width, file);
        }
    }
    fclose(file);
    return 0;
}

void resume_game()
{
    clear();
    refresh();
    curs_set(0);
    int rows, cols;
    noecho();
    getmaxyx(stdscr, rows, cols);
    rows -= 6;
    Game* main_game = calloc(1, sizeof(Game));
    int level;
    load_game(main_game, &level);
    MessageWindow* msg_win = init_message_window(cols, rows + 6, 0);
    MessageWindow* data_win = init_message_window(cols, rows + 6, 1);
    for(int i = 0; i < main_game->floors[level].height; i++)
    {
        for(int j = 0; j < main_game->floors[level].width; j++)
        {
            if(main_game->floors[level].printed_map[i][j])
            {
                char printed_ch = main_game->floors[level].map[i][j];
                int room_type = -1;
                for(int k = 0; k < main_game->floors[level].room_count; k++)
                {
                    int y = main_game->floors[level].rooms[k].position.y;
                    int x = main_game->floors[level].rooms[k].position.x;
                    int height = main_game->floors[level].rooms[k].height;
                    int width = main_game->floors[level].rooms[k].width;
                    if((i >= y) && (i < y + height) && (j >= x) && (j < x + width))
                        room_type = main_game->floors[level].rooms[k].type;
                }
                if((printed_ch == '@') || (printed_ch == '&') || (printed_ch == '%') || (printed_ch == '$')
                || (printed_ch == 'D') || (printed_ch == 'F') || (printed_ch == 'S') || (printed_ch == 'U') || (printed_ch == 'G'))
                {
                    attron(COLOR_PAIR(this_game_settings.hero_color));
                    mvprintw(i + 3, j, "%c", printed_ch);
                    attroff(COLOR_PAIR(this_game_settings.hero_color));
                }
                else if(printed_ch == 'L')
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(i + 3, j, "%c", printed_ch);
                    attroff(COLOR_PAIR(4));
                }
                else if(room_type == 1)
                {
                    attron(COLOR_PAIR(2));
                    mvprintw(i + 3, j, "%c", printed_ch);
                    attroff(COLOR_PAIR(2));
                }
                else if(room_type == 3)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(i + 3, j, "%c", printed_ch);
                    attroff(COLOR_PAIR(4));
                }
                else
                {
                    mvprintw(i + 3, j, "%c", printed_ch);
                }
            }
        }
    }
    refresh();
    character_move(main_game, msg_win, data_win, level);
    destroy_message_window(msg_win);
    destroy_message_window(data_win);
    refresh();
    curs_set(0);
    display_main_menu();
}
int does_save_exist() {
    char filename[50];
    snprintf(filename, sizeof(filename), "savegame_%s.dat", this_game_settings.player_name);

    return access(filename, F_OK) != -1;
}


int update_player_score(const char* username, int score, int gold, int done_game) {
    if(strcmp(username, "Guest") == 0)
        return 1;

    FILE* file = fopen(SCOREBOARD_FILE, "r");
    if (!file) {
        file = fopen(SCOREBOARD_FILE, "w");
        time_t current_time = time(NULL);
        fprintf(file, "%s %d %d %d %ld\n", username, score, gold, done_game, current_time);
        fclose(file);
        return 0;
    }

    char temp_filename[] = "scoreboard_temp.txt";
    FILE* temp_file = fopen(temp_filename, "w");

    char file_username[50];
    int file_score, file_gold, file_games;
    time_t first_play_time;
    int found = 0;

    while (fscanf(file, "%s %d %d %d %ld", file_username, &file_score, &file_gold, &file_games, &first_play_time) == 5) {
        if (strcmp(file_username, username) == 0) {
            file_score += score;
            file_gold += gold;
            file_games += done_game;
            found = 1;
        }
        fprintf(temp_file, "%s %d %d %d %ld\n", file_username, file_score, file_gold, file_games, first_play_time);
    }

    if (!found) {
        time_t current_time = time(NULL); 
        fprintf(temp_file, "%s %d %d %d %ld\n", username, score, gold, done_game, current_time);
    }

    fclose(file);
    fclose(temp_file);
    remove(SCOREBOARD_FILE);
    rename(temp_filename, SCOREBOARD_FILE);
}
