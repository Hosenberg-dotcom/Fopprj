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
    for(int i = 0; i < 4; i++) {
        main_game->floors[i].map = create_empty_map(cols, rows);
        main_game->floors[i].height = rows;
        main_game->floors[i].width = cols;
        main_game->floors[i].room_count = rand() % 4 + 6;
        generate_random_map(&(main_game->floors[i]));
        add_items_to_rooms(&(main_game->floors[i]), i);
    }
    for(int i = 0; i < 4; i++) main_game->floors[i].show_full_map = 0;

    MessageWindow* msg_win = init_message_window(cols, rows + 6, 0);
    MessageWindow* data_win = init_message_window(cols, rows + 6, 1);

    main_game->hero = creat_hero(this_game_settings.difficulty, this_game_settings.hero_symbol, this_game_settings.hero_color, 0, this_game_settings.difficulty, 1, 0);

    
    int random_room_index = (rand() % main_game->floors[0].room_count);
    Room* random_room = &(main_game->floors[0].rooms[random_room_index]);


    int x, y;
    do {
        x = random_room->position.x + (rand() % (random_room->width - 2)) + 1;
        y = random_room->position.y + (rand() % (random_room->height - 2)) + 1;
    } while (main_game->floors[0].map[y][x] != '.');  // تا زمانی که نقطه خالی پیدا شود

    main_game->hero.position.x = x;
    main_game->hero.position.y = y;
    main_game->floors[0].map[y][x] = main_game->hero.symbol;
    print_room(main_game, 0);
    refresh();
    character_move(main_game, msg_win, data_win, 0);

    destroy_message_window(msg_win);
    destroy_message_window(data_win);
    refresh();
    curs_set(0);
    display_main_menu();
}