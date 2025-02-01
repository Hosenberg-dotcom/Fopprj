#include "headers.h"

void check_and_pick_item(Game* main_game, int level, MessageWindow* msg_win) {
    Floor* current_floor = &main_game->floors[level];
    Room* current_room = NULL;
    Character* hero = &main_game->hero;

    // پیدا کردن اتاقی که بازیکن داخل آن قرار دارد
    for (int i = 0; i < current_floor->room_count; i++) {
        Room* room = &current_floor->rooms[i];
        if (hero->position.x >= room->position.x && hero->position.x < room->position.x + room->width &&
            hero->position.y >= room->position.y && hero->position.y < room->position.y + room->height) {
            current_room = room;
            break;
        }
    }
    
    if (!current_room) return; // اگر بازیکن در هیچ اتاقی نبود، تابع را ترک کن

    // بررسی آیتم‌های داخل اتاق
    for (int i = 0; i < current_room->food_count; i++) {
        if (current_room->room_foods[i].position.x == hero->position.x &&
            current_room->room_foods[i].position.y == hero->position.y) {
            
            // نمایش پیام برای برداشتن آیتم
            print_message(msg_win, "Pick up food? (y/n)");
            int ch = getch();
            if (ch == 'y') {
                // اضافه کردن غذا به بازیکن
                hero->my_foods[hero->food_count++] = current_room->room_foods[i];

                // حذف از اتاق
                for (int j = i; j < current_room->food_count - 1; j++) {
                    current_room->room_foods[j] = current_room->room_foods[j + 1];
                }
                current_room->food_count--;

                // حذف از نقشه
                current_floor->map[hero->position.y][hero->position.x] = '.';
                print_message(msg_win, "You found food!");
            }
            else
                print_message(msg_win, "");
            return;
        }
    }

    for (int i = 0; i < current_room->weapon_count; i++) {
        if (current_room->room_weapons[i].position.x == hero->position.x &&
            current_room->room_weapons[i].position.y == hero->position.y) {
            
            print_message(msg_win, "Pick up weapon? (y/n)");
            int ch = getch();
            if (ch == 'y') {
                hero->my_weapons[hero->weapon_count++] = current_room->room_weapons[i];

                for (int j = i; j < current_room->weapon_count - 1; j++) {
                    current_room->room_weapons[j] = current_room->room_weapons[j + 1];
                }
                current_room->weapon_count--;

                current_floor->map[hero->position.y][hero->position.x] = '.';
                print_message(msg_win, "You found weapon!");
            }
            else
                print_message(msg_win, "");
            return;

        }
    }

    for (int i = 0; i < current_room->spell_count; i++) {
        if (current_room->room_spells[i].position.x == hero->position.x &&
            current_room->room_spells[i].position.y == hero->position.y) {
            
            print_message(msg_win, "Pick up spell? (y/n)");
            int ch = getch();
            if (ch == 'y') {
                hero->my_spells[hero->spell_count++] = current_room->room_spells[i];

                for (int j = i; j < current_room->spell_count - 1; j++) {
                    current_room->room_spells[j] = current_room->room_spells[j + 1];
                }
                current_room->spell_count--;

                current_floor->map[hero->position.y][hero->position.x] = '.';
                print_message(msg_win, "You found spell!");
            }
            else
                print_message(msg_win, "");
            return;
        }
    }

    for (int i = 0; i < current_room->gold_count; i++) {
        if (current_room->golds[i].position.x == hero->position.x &&
            current_room->golds[i].position.y == hero->position.y) {
            
            print_message(msg_win, "Pick up gold? (y/n)");
            int ch = getch();
            if (ch == 'y') {
                switch(current_room->golds[i].type)
                {
                    case 0: hero->gold += 1; break;
                    case 1: hero->gold += 10; break;
                }

                for (int j = i; j < current_room->gold_count - 1; j++) {
                    current_room->golds[j] = current_room->golds[j + 1];
                }
                current_room->gold_count--;

                current_floor->map[hero->position.y][hero->position.x] = '.';
                print_message(msg_win, "You found gold!");
            }
            else
                print_message(msg_win, "");
            return;
        }
    }
}

/*void character_move(Game* main_game, MessageWindow* msg_win, MessageWindow* data_win, int level)
{
    int ch;
    char my_ch = '.';
    Point newPosition;
    int flag;
    while ((ch = getch()) != 'q') {
        flag = 0;
        newPosition = main_game->hero.position;
        switch (ch) {
            case '8': newPosition.y--; break;
            case '2': newPosition.y++; break;
            case '4': newPosition.x--; break;
            case '6': newPosition.x++; break;
            case '7': newPosition.y--; newPosition.x--; break;
            case '9': newPosition.y--; newPosition.x++; break;
            case '1': newPosition.y++; newPosition.x--; break;
            case '3': newPosition.y++; newPosition.x++; break;
            case 'm':
                flag = 1;
                toggle_map_display(main_game, level);
                break;
        }
        if (flag) continue;

        switch (main_game->floors[level].map[newPosition.y][newPosition.x]) {
            case '+': case '.': case '#':
                main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x] = my_ch;
                mvaddch(main_game->hero.position.y + 3, main_game->hero.position.x, my_ch);
                my_ch = mvinch(newPosition.y + 3, newPosition.x);
                main_game->floors[level].map[newPosition.y][newPosition.x] = main_game->hero.symbol;
                mvaddch(newPosition.y + 3, newPosition.x, main_game->hero.symbol);
                main_game->hero.position = newPosition;
                main_game->hero.gold += 1;
                if (my_ch == '+' || my_ch == '#')
                    update_map(main_game, level);
                
                check_and_pick_item(main_game, level, msg_win);

                print_data(data_win, main_game->hero, level);
                print_message(msg_win, "You found a sword!");
                break;
            case ' ': case '_': case '|':
                print_message(msg_win, "");
                break;
        }
        refresh();
    }
}*/
