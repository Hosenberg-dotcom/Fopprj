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
                mvprintw(i + 3, j, "%c", main_game->floors[level].map[i][j]);
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