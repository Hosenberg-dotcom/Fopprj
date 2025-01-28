#include "headers.h"
void character_move(Character* charecter, char** my_map)
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
            case '7': // 7 (بالا-چپ)
                newPosition.y--;
                newPosition.x--;
                break;
            case '9': // 9 (بالا-راست)
                newPosition.y--;
                newPosition.x++;
                break;
            case '1': // 1 (پایین-چپ)
                newPosition.y++;
                newPosition.x--;
                break;
            case '3': // 3 (پایین-راست)
                newPosition.y++;
                newPosition.x++;
                break; 
    }
    switch(my_map[newPosition.y - 2][newPosition.x])
    {
        case '+':
        case '.':
            my_map[charecter->position.y - 2][charecter->position.x] = my_ch;
            mvaddch(charecter->position.y, charecter->position.x, my_ch);
            my_ch = mvinch(newPosition.y, newPosition.x);
            my_map[newPosition.y - 2][newPosition.x] = charecter->symbol;
            mvaddch(newPosition.y, newPosition.x, charecter->symbol);
            charecter->position = newPosition;
            break;
        case '_':
            break;
        case '|':
            break;
        case '#':
            my_map[charecter->position.y - 2][charecter->position.x] = my_ch;
            mvaddch(charecter->position.y, charecter->position.x, my_ch);
            my_ch = mvinch(newPosition.y, newPosition.x);
            my_map[newPosition.y - 2][newPosition.x] = charecter->symbol;
            mvaddch(newPosition.y, newPosition.x, charecter->symbol);
            charecter->position = newPosition;
            break;
        case ' ':
            break;
    }
    refresh();
    }
    
}