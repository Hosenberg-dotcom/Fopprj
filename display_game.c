#include "headers.h"

void display_game() {
    clear();
    refresh();
    curs_set(0);
    int rows, cols;
    noecho();
    getmaxyx(stdscr, rows, cols);
    rows -= 6;
    Game* main_game = calloc(1, sizeof(Game));
    for(int i = 0; i < 4; i++)
    {
        main_game->floors[i].map = create_empty_map(cols, rows);
        main_game->floors[i].height = rows;
        main_game->floors[i].width = cols;
        main_game->floors[i].room_count = rand() % 4 + 6;
        generate_random_map(&(main_game->floors[i]));
        add_items_to_rooms(&(main_game->floors[i]), i);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mvprintw(i + 3, j,"%c", main_game->floors[0].map[i][j]);
        }
       
    }
    MessageWindow* msg_win = init_message_window(cols, rows + 6, 0);
    MessageWindow* data_menu = init_message_window(cols, rows + 6, 1);
    main_game->hero = creat_hero(this_game_settings.difficulty, this_game_settings.hero_symbol, this_game_settings.hero_color, 0, this_game_settings.difficulty, 1, 0);
    int flag = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(main_game->floors[0].map[i][j] == '.')
            {
                main_game->hero.position.y = i + 3;
                main_game->hero.position.x = j;
                mvprintw(main_game->hero.position.y, main_game->hero.position.x, "%c", main_game->hero.symbol);
                main_game->floors[0].map[main_game->hero.position.y - 3][main_game->hero.position.x] = main_game->hero.symbol;
                refresh();
                character_move(&(main_game->hero), main_game->floors[0].map, msg_win);
                flag = 1;
                break;
            }
            if(flag)
                break;
        }
    }
    destroy_message_window(msg_win);
    destroy_message_window(data_menu);
    refresh();
    curs_set(0);

    display_main_menu();
}