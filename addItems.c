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
            room->food_count = 0;
            room->weapon_count = 0;
            room->spell_count = 0;
            room->gold_count = MAX_ROOM_GOLDS;  
            room->monster_count = 1;
            room->trap_count = MAX_ROOM_TRAP;
        }

        int perv_x[100];
        int perv_y[100];
        int perv_Index = 0;
        int x = -2;
        int y = -2;

        // قرار دادن آیتم‌ها در مکان‌های تصادفی داخل اتاق
        for (int j = 0; j < room->food_count; j++) {
            do
            {
                x = room->position.x + (rand() % (room->width - 2)) + 1;
                y = room->position.y + (rand() % (room->height - 2)) + 1;
            } while (!check_item(perv_y, perv_x, perv_Index, y, x));
            perv_x[perv_Index] = x;
            perv_y[perv_Index] = y;
            perv_Index++;
            int chance = rand() % 10 >= 5;
            if(chance >= 5)
            {
                room->room_foods[j].health_care = 10;
                room->room_foods[j].power_raise = 0;
                room->room_foods[j].speed_raise = 0;
                room->room_foods[j].type = 0;
            }
            else if(chance >= 3)
            {
                room->room_foods[j].health_care = -10;
                room->room_foods[j].power_raise = 0;
                room->room_foods[j].speed_raise = 0;
                room->room_foods[j].type = 1;
            }
            else if(chance >= 1)
            {
                room->room_foods[j].health_care = 10;
                room->room_foods[j].power_raise = 0;
                room->room_foods[j].speed_raise = 1;
                room->room_foods[j].type = 2;
            }
            else if(chance == 0)
            {
                room->room_foods[j].health_care = 10;
                room->room_foods[j].power_raise = 1;
                room->room_foods[j].speed_raise = 0;
                room->room_foods[j].type = 3;
            }
            room->room_foods[j].position.x = x;
            room->room_foods[j].position.y = y;
            room->room_foods[j].symbol = 'O';
            my_floor->map[room->room_foods[j].position.y][room->room_foods[j].position.x] = 'O';
        }

        for (int j = 0; j < room->weapon_count; j++) {
            do
            {
                x = room->position.x + (rand() % (room->width - 2)) + 1;
                y = room->position.y + (rand() % (room->height - 2)) + 1;
            } while (!check_item(perv_y, perv_x, perv_Index, y, x));
            perv_x[perv_Index] = x;
            perv_y[perv_Index] = y;
            perv_Index++;
            int chance = rand() % 10;
            switch(chance)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    room->room_weapons[j].symbol = 'A';
                    room->room_weapons[j].collect_numbers = 20;
                    room->room_weapons[j].damage = 5;
                    room->room_weapons[j].range = 5;
                    room->room_weapons[j].range_type = 1;
                    room->room_weapons[j].type = 0;
                    break;
                case 4:
                case 5:
                case 6:
                    room->room_weapons[j].symbol = 'R';
                    room->room_weapons[j].collect_numbers = 10;
                    room->room_weapons[j].damage = 12;
                    room->room_weapons[j].range = 5;
                    room->room_weapons[j].range_type = 1;
                    room->room_weapons[j].type = 1;
                    break;
                case 7:
                case 8:
                    room->room_weapons[j].symbol = 'C';
                    room->room_weapons[j].collect_numbers = 8;
                    room->room_weapons[j].damage = 15;
                    room->room_weapons[j].range = 10;
                    room->room_weapons[j].range_type = 1;
                    room->room_weapons[j].type = 2;
                    break;
                case 9:
                    room->room_weapons[j].symbol = 'W';
                    room->room_weapons[j].collect_numbers = 1;
                    room->room_weapons[j].damage = 10;
                    room->room_weapons[j].range = 1;
                    room->room_weapons[j].range_type = 0;
                    room->room_weapons[j].type = 3;
                    break;
            }
            room->room_weapons[j].position.x = x;
            room->room_weapons[j].position.y = y;
            my_floor->map[room->room_weapons[j].position.y][room->room_weapons[j].position.x] = room->room_weapons[j].symbol;
        }

        for (int j = 0; j < room->spell_count; j++) {
            do
            {
                x = room->position.x + (rand() % (room->width - 2)) + 1;
                y = room->position.y + (rand() % (room->height - 2)) + 1;
            } while (!check_item(perv_y, perv_x, perv_Index, y, x));
            perv_x[perv_Index] = x;
            perv_y[perv_Index] = y;
            perv_Index++;
            int chance = rand() % 3;
            switch(chance)
            {
                case 0:
                    room->room_spells[j].type = 0;
                    break;
                case 1:
                    room->room_spells[j].type = 1;
                    break;
                case 2:
                    room->room_spells[j].type = 2;
                    break;
            }
            room->room_spells[j].time_left = 10;
            room->room_spells[j].position.x = x;
            room->room_spells[j].position.y = y;
            room->room_spells[j].symbol = 'P';
            my_floor->map[room->room_spells[j].position.y][room->room_spells[j].position.x] = 'P';
            room->room_spells[j].time_left = 10;
        }

        for (int j = 0; j < room->gold_count; j++) {
            do
            {
                x = room->position.x + (rand() % (room->width - 2)) + 1;
                y = room->position.y + (rand() % (room->height - 2)) + 1;
            } while (!check_item(perv_y, perv_x, perv_Index, y, x));
            perv_x[perv_Index] = x;
            perv_y[perv_Index] = y;
            perv_Index++;
            int chance = rand() % 10;
            switch(chance)
            {
                case 0:
                    room->golds[j].type = 0;
                    break;
                default:
                    room->golds[j].type = 1;
                    break;
            }
            room->golds[j].position.x = x;
            room->golds[j].position.y = y;
            room->golds[j].symbol = 'L';
            my_floor->map[room->golds[j].position.y][room->golds[j].position.x] = 'L';
        }

        for (int j = 0; j < room->trap_count; j++) {
            do
            {
                x = room->position.x + (rand() % (room->width - 2)) + 1;
                y = room->position.y + (rand() % (room->height - 2)) + 1;
            } while (!check_item(perv_y, perv_x, perv_Index, y, x));
            perv_x[perv_Index] = x;
            perv_y[perv_Index] = y;
            perv_Index++;
            room->trap_position[j].x = x;
            room->trap_position[j].y = y;
            //my_floor->map[room->trap_position[j].y][room->trap_position[j].x] = 'T';
        }

        if (room->type != 1) { 
            for (int j = 0; j < room->monster_count; j++) {
                do
                {
                    x = room->position.x + (rand() % (room->width - 2)) + 1;
                    y = room->position.y + (rand() % (room->height - 2)) + 1;
                } while (!check_item(perv_y, perv_x, perv_Index, y, x));
                perv_x[perv_Index] = x;
                perv_y[perv_Index] = y;
                perv_Index++;
                
                if(room->monster[j].type == 2)
                {
                    room->monster[j].type = 4;
                    room->monster[j].damage = 30;
                    room->monster[j].health = 30;
                    room->monster[j].move_left = 10;
                    room->monster[j].symbol = 'U';
                }
                else
                {
                    int chance = rand() % 4;
                    switch(chance)
                    {
                        case 0:
                            room->monster[j].type = 0;
                            room->monster[j].damage = 5;
                            room->monster[j].health = 5;
                            room->monster[j].move_left = 5;
                            room->monster[j].symbol = 'D';
                            break;
                        case 1:
                            room->monster[j].type = 1;
                            room->monster[j].damage = 10;
                            room->monster[j].health = 10;
                            room->monster[j].move_left = 8;
                            room->monster[j].symbol = 'F';
                            break;
                        case 2:
                            room->monster[j].type = 2;
                            room->monster[j].damage = 15;
                            room->monster[j].health = 15;
                            room->monster[j].move_left = 15;
                            room->monster[j].symbol = 'G';
                            break;
                        case 3:
                            room->monster[j].type = 3;
                            room->monster[j].damage = 20;
                            room->monster[j].health = 20;
                            room->monster[j].move_left = 10000;
                            room->monster[j].symbol = 'S';
                            break;
                    }
                }
                room->monster[j].position = malloc(sizeof(Point));
                room->monster[j].position->x = x;
                room->monster[j].position->y = y;
                my_floor->map[room->monster[j].position->y][room->monster[j].position->x] = room->monster[j].symbol;
            }
        }
    }
}

int check_item(int* perv_y, int* perv_x, int perv_Index, int y, int x) {
    int flag = -1;
    for(int i = 0; i < perv_Index; i++)
    {
        if(perv_x[i] == x && perv_y[i] == y)
        {
            flag++;
            break;
        }
    }
    return flag;
}