#include "headers.h"

Character creat_hero(int health, char symbol, int color, int gold, int food_count, int weapon_count, int spell_count)
{
    Character hero;
    hero.color = color;
    hero.food_count = food_count;
    hero.gold = gold;
    hero.health = health;
    hero.spell_count =spell_count;
    hero.symbol = symbol;
    hero.weapon_count = weapon_count;
    return hero;
}

void character_move(Character* charecter, char** my_map, MessageWindow* msg_win,MessageWindow* data_win, int level)
{
    int ch;
    char my_ch = '.';
    Point newPosition;
    while((ch = getch()) != 'q')
    {
        newPosition = charecter->position;
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
    }
    switch(my_map[newPosition.y - 3][newPosition.x])
    {
        case '+':
        case '.':
        case '#':
            my_map[charecter->position.y - 3][charecter->position.x] = my_ch;
            mvaddch(charecter->position.y, charecter->position.x, my_ch);
            my_ch = mvinch(newPosition.y, newPosition.x);
            my_map[newPosition.y - 3][newPosition.x] = charecter->symbol;
            mvaddch(newPosition.y, newPosition.x, charecter->symbol);
            charecter->position = newPosition;
            charecter->gold += 1;
            print_data(data_win, *charecter, level);
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
