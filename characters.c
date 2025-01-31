#include "headers.h"

Character creat_hero(int health, char symbol, int color, int gold, int food_count, int weapon_count, int spell_count)
{
    Character hero;
    hero.color = color;
    hero.food_count = food_count;
    hero.gold = gold;
    hero.position.x = 0;
    hero.position.y = 0;
    hero.health = health;
    hero.spell_count =spell_count;
    hero.symbol = symbol;
    hero.weapon_count = weapon_count;
    return hero;
}

void character_move(Game* main_game, MessageWindow* msg_win,MessageWindow* data_win, int level)
{
    int ch;
    char my_ch = '.';
    Point newPosition;
    int flag;
    while((ch = getch()) != 'q')
    {
        flag = 0;
        newPosition = main_game->hero.position;
        switch (ch) {
            
            case '8':
                newPosition.y--;
                break;
            case '2':
                newPosition.y++;
                break;
            case '4':
               newPosition.x--;
                break;
            
            case '6':
                newPosition.x++;
                break;
            case '7': 
                newPosition.y--;
                newPosition.x--;
                break;
            case '9': 
                newPosition.y--;
                newPosition.x++;
                break;
            case '1':
                newPosition.y++;
                newPosition.x--;
                break;
            case '3':
                newPosition.y++;
                newPosition.x++;
                break; 
            case 'm':
                flag = 1;
                toggle_map_display(main_game, level);
                break;
    }
    if(flag)
        continue;
    switch(main_game->floors[level].map[newPosition.y][newPosition.x])
    {
        case '+':
        case '.':
        case '#':
            main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x] = my_ch;
            mvaddch(main_game->hero.position.y + 3, main_game->hero.position.x, my_ch);
            my_ch = main_game->floors[level].map[newPosition.y][newPosition.x];
            main_game->floors[level].map[newPosition.y][newPosition.x] = main_game->hero.symbol;
            mvaddch(newPosition.y + 3, newPosition.x, main_game->hero.symbol);
            main_game->hero.position = newPosition;
            main_game->hero.gold += 1;
            //if(my_ch == '+') print_room(main_game, level);
            //if(my_ch == '#') print_corridors(main_game, level);
            if(my_ch == '+' || my_ch == '#')
            {
                //main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x] = my_ch;
                update_map(main_game, level);
                //main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x] = main_game->hero.symbol;
                //mvaddch(main_game->hero.position.y + 3, main_game->hero.position.x, main_game->hero.symbol);
            }
            //update_fog(fog_window, main_game, level);
            print_data(data_win, main_game->hero, level);
            print_message(msg_win, "You found a sword!");
            break;
        case ' ':
        case '_':
        case '|':
            print_message(msg_win, "");
            break;
    }
    refresh();
    }
    
}
