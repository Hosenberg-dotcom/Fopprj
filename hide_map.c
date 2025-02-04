#include "headers.h"

void print_room(Game* main_game, int level) {
    for (int r = 0; r < main_game->floors[level].room_count; r++) {
        Room* room = &main_game->floors[level].rooms[r];

        if (main_game->hero.position.x >= room->position.x && main_game->hero.position.x < room->position.x + room->width &&
            main_game->hero.position.y >= room->position.y && main_game->hero.position.y < room->position.y + room->height) {
        
            for (int i = 0; i < room->height; i++) {
                for (int j = 0; j < room->width; j++) {
                    int x = room->position.x + j;
                    int y = room->position.y + i;
                    char printed_ch = main_game->floors[level].map[y][x];
                    if((printed_ch == '@') || (printed_ch == '&') || (printed_ch == '%') || (printed_ch == '$')
                        || (printed_ch == 'D') || (printed_ch == 'F') || (printed_ch == 'S') || (printed_ch == 'U') || (printed_ch == 'G'))
                        {
                            attron(COLOR_PAIR(3));
                            mvprintw(y + 3, x, "%c", printed_ch);
                            attroff(COLOR_PAIR(3));
                        }
                        else if(printed_ch == 'L')
                        {
                            attron(COLOR_PAIR(4));
                            mvprintw(y + 3, x, "%c", printed_ch);
                            attroff(COLOR_PAIR(4));
                        }
                        else if(main_game->floors[level].rooms[r].type == 1)
                        {
                            attron(COLOR_PAIR(2));
                            mvprintw(y + 3, x, "%c", printed_ch);
                            attroff(COLOR_PAIR(2));
                        }
                        else
                        {
                            mvprintw(y + 3, x, "%c", printed_ch);
                        }
                    main_game->floors[level].printed_map[y][x] = 1;
                }
            }
            refresh();
            return;
        }
    }
}

void print_corridors(Game* main_game, int level) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (int d = 0; d < 4; d++) {
        for (int i = 1; i <= 5; i++) {
            int new_x = main_game->hero.position.x + i * directions[d][0];
            int new_y = main_game->hero.position.y + i * directions[d][1];

            if (new_x < 0 || new_x >= main_game->floors[level].width || new_y < 0 || new_y >= main_game->floors[level].height) break;

            if (main_game->floors[level].map[new_y][new_x] == '#' || main_game->floors[level].printed_map[new_y][new_x]) {
                int printed_ch = main_game->floors[level].map[new_y][new_x];
                int room_type = -1;
                for(int k = 0; k < main_game->floors[level].room_count; k++)
                {
                    int y = main_game->floors[level].rooms[k].position.y;
                    int x = main_game->floors[level].rooms[k].position.x;
                    int height = main_game->floors[level].rooms[k].height;
                    int width = main_game->floors[level].rooms[k].width;
                    if((new_y >= y) && (new_y < y + height) && (new_x >= x) && (new_x < x + width))
                        room_type = main_game->floors[level].rooms[k].type;
                }
                if((printed_ch == '@') || (printed_ch == '&') || (printed_ch == '%') || (printed_ch == '$')
                || (printed_ch == 'D') || (printed_ch == 'F') || (printed_ch == 'S') || (printed_ch == 'U') || (printed_ch == 'G'))
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(new_y + 3, new_x, "%c", printed_ch);
                    attroff(COLOR_PAIR(3));
                }
                else if(printed_ch == 'L')
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(new_y + 3, new_x, "%c", printed_ch);
                    attroff(COLOR_PAIR(4));
                }
                else if(room_type == 1)
                {
                    attron(COLOR_PAIR(2));
                    mvprintw(new_y + 3, new_x, "%c", printed_ch);
                    attroff(COLOR_PAIR(2));
                }
                else if(room_type == 3)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(new_y + 3, new_x, "%c", printed_ch);
                    attroff(COLOR_PAIR(4));
                }
                else
                {
                    mvprintw(new_y + 3, new_x, "%c", printed_ch);
                }
                main_game->floors[level].printed_map[new_y][new_x] = 1;
            } else {
                break;
            }
        }
    }
}

void toggle_map_display(Game* main_game, int level) {
    main_game->floors[level].show_full_map = !main_game->floors[level].show_full_map;
    if (main_game->floors[level].show_full_map) {
        for (int i = 0; i < main_game->floors[level].height; i++) {
            for (int j = 0; j < main_game->floors[level].width; j++) {
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
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 3, j, "%c", printed_ch);
                    attroff(COLOR_PAIR(3));
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
    } else {
        for (int i = 0; i < main_game->floors[level].height; i++) {
            for (int j = 0; j < main_game->floors[level].width; j++) {
                if (!main_game->floors[level].printed_map[i][j]) {
                    mvprintw(i + 3, j, " ");
                }
            }
        }
    }
    refresh();
}

void update_map(Game* main_game, int level) {
    if (!main_game->floors[level].show_full_map) {
        print_room(main_game, level);
        print_corridors(main_game, level);
    }
    refresh();
}
