#include "headers.h"

void add_items_to_rooms(Floor* my_floor, int floor_index) {
    for (int i = 0; i < my_floor->room_count; i++) {
        Room* room = &my_floor->rooms[i];

        // تنظیم نوع اتاق
        if (floor_index == MAX_FLOORS - 1 && i == my_floor->room_count - 1) {
            room->type = 2;  // اتاق گنج فقط در آخرین طبقه
        } else if (rand() % 5 == 0) {
            room->type = 1;  // اتاق طلسم با احتمال 20٪
        } else {
            room->type = 0;  // اتاق معمولی
        }

        // بررسی مقدار `MAX_ROOM_SPELLS` برای جلوگیری از تقسیم بر صفر
        int max_spells = (MAX_ROOM_SPELLS > 1) ? MAX_ROOM_SPELLS - 1 : 1;

        // افزودن آیتم‌ها بر اساس نوع اتاق
        if (room->type == 0) {  // اتاق معمولی
            room->food_count = rand() % MAX_ROOM_FOOD;
            room->weapon_count = rand() % MAX_ROOM_WEAPONS;
            room->spell_count = rand() % max_spells;
            room->gold_count = rand() % MAX_ROOM_GOLDS;
            room->monster_count = rand() % MAX_ROOM_MONSTERS;
            room->trap_count = rand() % MAX_ROOM_TRAP;
        } 
        else if (room->type == 1) {  // اتاق طلسم (بدون هیولا)
            room->food_count = rand() % MAX_ROOM_FOOD;
            room->weapon_count = rand() % MAX_ROOM_WEAPONS;
            room->spell_count = rand() % max_spells + 1;  // حداقل یک طلسم
            room->gold_count = rand() % (MAX_ROOM_GOLDS / 2);
            room->monster_count = 0;
            room->trap_count = rand() % MAX_ROOM_TRAP;
        } 
        else if (room->type == 2) {  // اتاق گنج (فقط در طبقه آخر)
            room->food_count = rand() % MAX_ROOM_FOOD;
            room->weapon_count = rand() % (MAX_ROOM_WEAPONS + 1);
            room->spell_count = rand() % (max_spells + 1);
            room->gold_count = MAX_ROOM_GOLDS;  
            room->monster_count = rand() % MAX_ROOM_MONSTERS;
            room->trap_count = rand() % MAX_ROOM_TRAP;
        }

        // قرار دادن آیتم‌ها در مکان‌های تصادفی داخل اتاق
        for (int j = 0; j < room->food_count; j++) {
            room->room_foods[j].position.x = room->position.x + (rand() % (room->width - 2)) + 1;
            room->room_foods[j].position.y = room->position.y + (rand() % (room->height - 2)) + 1;
            room->room_foods[j].symbol = 'F';
            my_floor->map[room->room_foods[j].position.y][room->room_foods[j].position.x] = 'F';
        }

        for (int j = 0; j < room->weapon_count; j++) {
            room->room_weapons[j].position.x = room->position.x + (rand() % (room->width - 2)) + 1;
            room->room_weapons[j].position.y = room->position.y + (rand() % (room->height - 2)) + 1;
            room->room_weapons[j].symbol = 'W';
            my_floor->map[room->room_weapons[j].position.y][room->room_weapons[j].position.x] = 'W';
        }

        for (int j = 0; j < room->spell_count; j++) {
            room->room_spells[j].position.x = room->position.x + (rand() % (room->width - 2)) + 1;
            room->room_spells[j].position.y = room->position.y + (rand() % (room->height - 2)) + 1;
            room->room_spells[j].symbol = 'S';
            my_floor->map[room->room_spells[j].position.y][room->room_spells[j].position.x] = 'S';
        }

        for (int j = 0; j < room->gold_count; j++) {
            room->golds[j].position.x = room->position.x + (rand() % (room->width - 2)) + 1;
            room->golds[j].position.y = room->position.y + (rand() % (room->height - 2)) + 1;
            room->golds[j].symbol = 'G';
            my_floor->map[room->golds[j].position.y][room->golds[j].position.x] = 'G';
        }

        for (int j = 0; j < room->trap_count; j++) {
            room->trap_position[j].x = room->position.x + (rand() % (room->width - 2)) + 1;
            room->trap_position[j].y = room->position.y + (rand() % (room->height - 2)) + 1;
            my_floor->map[room->trap_position[j].y][room->trap_position[j].x] = 'T';
        }

        if (room->type != 1) { 
            for (int j = 0; j < room->monster_count; j++) {
                room->monster[j].position = malloc(sizeof(Point));
                room->monster[j].position->x = room->position.x + (rand() % (room->width - 2)) + 1;
                room->monster[j].position->y = room->position.y + (rand() % (room->height - 2)) + 1;
                room->monster[j].symbol = 'M';
                my_floor->map[room->monster[j].position->y][room->monster[j].position->x] = 'M';
            }
        }
    }
}
