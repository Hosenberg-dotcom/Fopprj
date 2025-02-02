#include "headers.h"

void speed_spell(Game* main_game)
{
    if(main_game->hero.speed_spell != 1)
    {
        main_game->hero.spell_time_left--;
        if(main_game->hero.speed_spell == 2)
            main_game->hero.speed_spell = 3;
        else if(main_game->hero.speed_spell == 3)
            main_game->hero.speed_spell = 2;
        if(main_game->hero.spell_time_left == 0)
        {
            main_game->hero.selected_spell = -1;
            main_game->hero.speed_spell = 1;
        }
    }
}
void health_speed(Game* main_game, int* last_health)
{
    if(main_game->hero.health_spell != 1)
    {
    if(main_game->hero.health_spell == 2)
    {
        *last_health = main_game->hero.health;
        //main_game->hero.spell_time_left--;
        main_game->hero.health_spell = 3;
    }
    else if(main_game->hero.health_spell == 3)
        main_game->hero.spell_time_left--;
    if(main_game->hero.spell_time_left == 0)
    {
        main_game->hero.selected_spell = -1;
        main_game->hero.speed_spell = 1;
        main_game->hero.health = *last_health;
    }

    }
}
void damage_spell(Game* main_game)
{
    if(main_game->hero.damage_spell != 1)
    {
        if(main_game->hero.damage_spell == 2)
        {
            main_game->hero.my_weapons[main_game->hero.selected_weapon].damage *= 2;
            main_game->hero.spell_time_left--;
            main_game->hero.damage_spell = 3;
        }
        else if(main_game->hero.spell_time_left > 0)
        {
            main_game->hero.spell_time_left--;
        }
        else
        {
            main_game->hero.selected_spell = -1;
            main_game->hero.damage_spell = 1;
        }
    }
}
void attack(Game* main_game, MessageWindow* msg_win, int level)
{
    if(main_game->hero.selected_weapon < 0)
    {
        print_message(msg_win, "You don't have any weapon!");
    }
    else if(main_game->hero.my_weapons[main_game->hero.selected_weapon].range_type == 0)
    {
        attack_melee(main_game, level, msg_win);
    }
    else
    {
        attack_ranged(main_game, level, msg_win);
    }
}
void attack_melee(Game* main_game, int level, MessageWindow* msg_win) {
    Character* hero = &main_game->hero;
    Weapons* weapon = &hero->my_weapons[hero->selected_weapon];

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            Point position;
            position.x = hero->position.x + j;
            position.y = hero->position.y + i;
            if (i == 0 && j == 0) continue;
            hit_monster(main_game, level, msg_win, position);
        }
    }
}
void remove_dead_monsters(Game* main_game, int level) {
    for (int r = 0; r < main_game->floors[level].room_count; r++) {
        Room* room = &main_game->floors[level].rooms[r];

        for (int m = 0; m < room->monster_count; m++) {
            if (room->monster[m].health <= 0) {
                main_game->floors[level].map[room->monster[m].position->y][room->monster[m].position->x] = '.';
                mvaddch(room->monster[m].position->y + 3, room->monster[m].position->x, '.');
                free(room->monster[m].position);
                
                for (int k = m; k < room->monster_count - 1; k++) {
                    room->monster[k] = room->monster[k + 1];
                }
                room->monster_count--;
                m--;
            }
        }
    }
}
void attack_ranged(Game* main_game, int level, MessageWindow* msg_win) {

    char direction = getch();
    int dx = 0, dy = 0;
    main_game->hero.my_weapons[main_game->hero.selected_weapon].collect_numbers--;
    switch (direction) {
        case '8': dy = -1; break;  
        case '2': dy = 1; break;   
        case '4': dx = -1; break;  
        case '6': dx = 1; break;   
        case '7': dx = -1; dy = -1; break;  
        case '9': dx = 1; dy = -1; break;  
        case '1': dx = -1; dy = 1; break;   
        case '3': dx = 1; dy = 1; break;    
        default:
            print_message(msg_win, "Invalid direction!");
            return;
    }
        check_projectile_hit(main_game, level, dy, dx, msg_win);
        remove_weapon_if_empty(&main_game->hero, msg_win);
}
void check_projectile_hit(Game* main_game, int level, int dy, int dx, MessageWindow* msg_win) {
    Point newPosition;
    newPosition.x = main_game->hero.position.x;
    newPosition.y = main_game->hero.position.y;
    if((main_game->floors[level].map[newPosition.y + dy][newPosition.x + dx] != '.') && (main_game->floors[level].map[newPosition.y + dy][newPosition.x + dx] != 'U') && (main_game->floors[level].map[newPosition.y + dy][newPosition.x + dx] != 'D') && (main_game->floors[level].map[newPosition.y + dy][newPosition.x + dx] != 'S') && (main_game->floors[level].map[newPosition.y + dy][newPosition.x + dx] != 'G') && (main_game->floors[level].map[newPosition.y + dy][newPosition.x + dx] != 'F'))
    {
        print_message(msg_win, "You can't shoot this way!");
        return;
    }
    int step_counter = 0;
    while(1)
    {
        newPosition.x += dx;
        newPosition.y += dy;
        if((step_counter + 1) > main_game->hero.my_weapons[main_game->hero.selected_weapon].range)
        {
            newPosition.x -= dx;
            newPosition.y -= dy;
            find_and_put_down_weapon(main_game, level, newPosition, msg_win);
            break;
        }
        else if(main_game->floors[level].map[newPosition.y][newPosition.x] == '.')
        {
            step_counter++;
            continue;
        }
        else if(main_game->floors[level].map[newPosition.y][newPosition.x] == 'U' || main_game->floors[level].map[newPosition.y][newPosition.x] == 'D' || main_game->floors[level].map[newPosition.y][newPosition.x] == 'S' || main_game->floors[level].map[newPosition.y][newPosition.x] == 'G' || main_game->floors[level].map[newPosition.y][newPosition.x] == 'F')
        {
            step_counter++;
            hit_monster(main_game, level, msg_win, newPosition);
            break;
        }
        else
        {
            step_counter++;
            newPosition.x -= dx;
            newPosition.y -= dy;
            find_and_put_down_weapon(main_game, level, newPosition, msg_win);
            break;
        }
    }
}
void remove_weapon_if_empty(Character* hero, MessageWindow* msg_win) {
    if (hero->my_weapons[hero->selected_weapon].collect_numbers <= 0) {
        print_message(msg_win, "Your weapon broke!");
        
        for (int i = hero->selected_weapon; i < hero->weapon_count - 1; i++) {
            hero->my_weapons[i] = hero->my_weapons[i + 1];
        }
        hero->weapon_count--;
        hero->selected_weapon = -1;
    }
}
void find_and_put_down_weapon(Game* main_game, int level, Point position, MessageWindow* msg_win) {
    Room* current_room = NULL;

    for (int i = 0; i < main_game->floors[level].room_count; i++) {
        Room* room = &main_game->floors[level].rooms[i];
        if (position.x >= room->position.x && position.x < room->position.x + room->width &&
            position.y >= room->position.y && position.y < room->position.y + room->height) {
            current_room = room;
            break;
        }
    }
    if(current_room->weapon_count >= MAX_ROOM_WEAPONS)
    {
        print_message(msg_win, "Rooms weapons are max can't drop weapon!");

    }
    else if (current_room != NULL && current_room->weapon_count < MAX_ROOM_WEAPONS) {
        Weapons dropped_weapon = main_game->hero.my_weapons[main_game->hero.selected_weapon];

        dropped_weapon.collect_numbers = 1;
        dropped_weapon.position = position;
        current_room->room_weapons[current_room->weapon_count++] = dropped_weapon;

        main_game->floors[level].map[position.y][position.x] = dropped_weapon.symbol;
        mvaddch(position.y + 3, position.x, dropped_weapon.symbol);
        print_message(msg_win, "Weapon dropped on the ground!");
    }
}
void hit_monster(Game* main_game, int level, MessageWindow* msg_win, Point position) {
    for (int i = 0; i < main_game->floors[level].room_count; i++) {
        Room* room = &main_game->floors[level].rooms[i];

        for (int j = 0; j < room->monster_count; j++) {
            Monsters* monster = &room->monster[j];

            if ((monster->position->x == position.x) && (monster->position->y == position.y)) {
                monster->health -= main_game->hero.my_weapons[main_game->hero.selected_weapon].damage;
                print_message(msg_win, "You score an excellent hit on a monster!");
                remove_dead_monsters(main_game, level);
                return;
            }
        }
    }
}
