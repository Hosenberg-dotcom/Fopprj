#include "headers.h"

int how_much_monster_nearby(Game* main_game, int level) {
    int monster_counter = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int new_x = main_game->hero.position.x + j;
            int new_y = main_game->hero.position.y + i;

            if (new_x < 0 || new_x >= main_game->floors[level].width || 
                new_y < 0 || new_y >= main_game->floors[level].height || 
                (i == 0 && j == 0)) {
                continue;
            }

            char a = main_game->floors[level].map[new_y][new_x];
            if (a == 'U' || a == 'D' || a == 'F' || a == 'G' || a == 'S') {
                monster_counter++;
            }
        }
    }
    
    return monster_counter;
}


void monster_attack(Game *main_game, int level, MessageWindow *msg_win, int monster_near) {
    int index = -1;
    for(int i = 0; i < main_game->floors[level].room_count; i++)
    {
        int x = main_game->floors[level].rooms[i].position.x;
        int y = main_game->floors[level].rooms[i].position.y;
        if((main_game->hero.position.x >= x) && (main_game->hero.position.x < x + main_game->floors[level].rooms[i].width) &&
           (main_game->hero.position.y >= y) && (main_game->hero.position.y < y + main_game->floors[level].rooms[i].height))
           {
            index = i;
            break;
           }
    }
    for(int i = 0; i < monster_near; i++)
    {
        int flag = 0;
        int x = main_game->floors[level].rooms[index].monster[i].position.x;
        int y = main_game->floors[level].rooms[index].monster[i].position.y;
        for(int j = - 1; j < 2; j++)
        {
            for(int k = - 1; k < 2; k++)
            if((main_game->hero.position.x + j == x) && (main_game->hero.position.y + k == y))
            {
                main_game->hero.health -= main_game->floors[level].rooms[index].monster[i].damage;
                print_message(msg_win, "monster score an excellent hit on you!");
                flag = 1;
                break;
            }
            if(flag)
                break;
        }
    }
}

void monster_chase(Game *main_game, int level, int room_index) {
        Room *room = &main_game->floors[level].rooms[room_index];

        for (int j = 0; j < room->monster_count; j++) {
            Monsters *monster = &room->monster[j];
                    if(monster->move_left)
                    {
                    Point temp = (monster->position);
                    pass_finding(&(monster->position), &(main_game->hero.position), main_game, level);
                    main_game->floors[level].map[temp.y][temp.x] = '.';
                    attron(COLOR_PAIR(6));
                    mvaddch(temp.y + 3, temp.x, '.');
                    attroff(COLOR_PAIR(6));
                    main_game->floors[level].map[monster->position.y][monster->position.x] = monster->symbol;
                    attron(COLOR_PAIR(this_game_settings.hero_color));
                    mvaddch(monster->position.y + 3, monster->position.x, monster->symbol);
                    attroff(COLOR_PAIR(this_game_settings.hero_color));
                    monster->move_left--;
                    }
            }
        
    
}

int is_in_monster_room(Game *main_game, int level) {
    for (int i = 0; i < main_game->floors[level].room_count; i++) {
        Room *room = &main_game->floors[level].rooms[i];

       
        if (main_game->hero.position.x >= room->position.x && 
            main_game->hero.position.x < room->position.x + room->width &&
            main_game->hero.position.y >= room->position.y && 
            main_game->hero.position.y < room->position.y + room->height) {
            
           
            if (room->monster_count > 0) {
                return i + 1; 
            }
        }
    }
    return 0; 
}

int pass_finding(Point* start, Point* destination, Game* main_game, int level)
{
    if((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && (main_game->floors[level].map[start->y][start->x - 1] == '.'))
        start->x = start->x - 1;
    else if((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && (main_game->floors[level].map[start->y][start->x + 1] == '.'))
        start->x = start->x + 1;
    else if((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && (main_game->floors[level].map[start->y + 1][start->x] == '.'))
        start->y = start->y + 1;
    else if((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && (main_game->floors[level].map[start->y - 1][start->x] == '.'))
        start->y = start->y - 1;
    else
    {

    }
    return 1;
}