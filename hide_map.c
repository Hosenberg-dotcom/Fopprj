#include "headers.h"

void print_room(Game* main_game, int level) {
    for (int r = 0; r < main_game->floors[level].room_count; r++) {
        Room* room = &main_game->floors[level].rooms[r];

        // بررسی اینکه پلیر داخل این اتاق هست یا نه
        if (main_game->hero.position.x >= room->position.x && main_game->hero.position.x < room->position.x + room->width &&
            main_game->hero.position.y >= room->position.y && main_game->hero.position.y < room->position.y + room->height) {
            
            // نمایش کل اتاق
            for (int i = 0; i < room->height; i++) {
                for (int j = 0; j < room->width; j++) {
                    int x = room->position.x + j;
                    int y = room->position.y + i;
                    
                    mvprintw(y + 3, x, "%c", main_game->floors[level].map[y][x]);
                    main_game->floors[level].printed_map[y][x] = 1; // ثبت‌شده به عنوان پرینت شده
                }
            }
            refresh();
            return;
        }
    }
}

void print_corridors(Game* main_game, int level) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // راست، چپ، پایین، بالا

    for (int d = 0; d < 4; d++) {
        for (int i = 1; i <= 5; i++) {
            int new_x = main_game->hero.position.x + i * directions[d][0];
            int new_y = main_game->hero.position.y + i * directions[d][1];

            if (new_x < 0 || new_x >= main_game->floors[level].width || new_y < 0 || new_y >= main_game->floors[level].height) break;

            if (main_game->floors[level].map[new_y][new_x] == '#' || main_game->floors[level].printed_map[new_y][new_x]) {
                mvprintw(new_y + 3, new_x, "%c", main_game->floors[level].map[new_y][new_x]);
                main_game->floors[level].printed_map[new_y][new_x] = 1; // ذخیره در آرایه
            } else {
                break;
            }
        }
    }
}

// تابعی برای مدیریت دکمه `M`
void toggle_map_display(Game* main_game, int level) {
    main_game->floors[level].show_full_map = !main_game->floors[level].show_full_map;
    if (main_game->floors[level].show_full_map) {
        // نمایش کل نقشه
        for (int i = 0; i < main_game->floors[level].height; i++) {
            for (int j = 0; j < main_game->floors[level].width; j++) {
                mvprintw(i + 3, j, "%c", main_game->floors[level].map[i][j]);
            }
        }
    } else {
        // مخفی‌سازی قسمت‌های دیده نشده
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

// به‌روزرسانی نمایش نقشه در هر حرکت
void update_map(Game* main_game, int level) {
    if (!main_game->floors[level].show_full_map) {
        print_room(main_game, level);
        print_corridors(main_game, level);
    }
    refresh();
}
