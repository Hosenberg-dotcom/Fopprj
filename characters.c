#include "headers.h"

Character creat_hero(int health, char symbol, int color, int gold, int food_count, int weapon_count, int spell_count)
{
    Character hero;
    hero.color = color;
    hero.food_count = food_count / 10;
    for(int i = 0; i < food_count / 10; i++)
    {
        hero.my_foods[i].type = 0;
        hero.my_foods[i].health_care = 10;
        hero.my_foods[i].power_raise = 0;
        hero.my_foods[i].speed_raise = 0;
        hero.my_foods[i].symbol = 'O';
    }
    hero.gold = gold;
    hero.position.x = 0;
    hero.position.y = 0;
    hero.health = health;
    hero.spell_count =spell_count;
    hero.symbol = symbol;
    hero.weapon_count = weapon_count;
    hero.my_weapons[0].type = 4;
    hero.my_weapons[0].damage = 5;
    hero.my_weapons[0].range = 1;
    hero.my_weapons[0].range_type = 0;
    hero.my_weapons[0].symbol = 'M';
    hero.selected_weapon = 0;
    hero.selected_spell = -1;
    hero.speed_spell = 1;
    hero.health_spell = 1;
    hero.damage_spell = 1;
    hero.spell_time_left = 0;
    return hero;
}

void character_move(Game* main_game, MessageWindow* msg_win,MessageWindow* data_win, int level)
{
    int ch;
    char my_ch = '.';
    Point newPosition;
    int flag;
    int break_point = 1;
    int monster_counter;
    int room_index;
    int last_health;
    print_data(data_win, main_game->hero, level);
    while(break_point && ((ch = getch()) != 'q'))
    {
        if(main_game->hero.health <= 0)
        {
            print_message(msg_win, "You died!");
            getch();
            update_player_score(this_game_settings.player_name, main_game->hero.gold * (1 + level ), main_game->hero.gold, 0);
            display_main_menu();
            return;
        }
        if(level == 4 && main_game->floors[level].rooms[0].monster_count == 0)
        {
            print_message(msg_win, "You won!");
            getch();
            update_player_score(this_game_settings.player_name, main_game->hero.gold * (1 + level ), main_game->hero.gold, 1);
            display_main_menu();
            return;
        }
        speed_spell(main_game);
        health_speed(main_game, &last_health);
        damage_spell(main_game);
        print_message(msg_win, "");
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
            case 'i':
                show_combined_item_menu(main_game, msg_win, data_win, level);
                print_message(msg_win, "");
                print_data(data_win, main_game->hero, level);
                refresh();
                flag = 1;
                break;
            case 's':
                print_message(msg_win, "Do you want to save the game? if yes press: y");
                char ans = getch();
                if(ans == 'y'){
                    int did_it_save = save_game(main_game, level);
                    int score_save = update_player_score(this_game_settings.player_name, main_game->hero.gold * (1 + level ), main_game->hero.gold, 0);
                    if(score_save) print_message(msg_win, "You can't save a Guest game!");
                    if(did_it_save == 1) print_message(msg_win, "You can't save a Guest game!");
                    else if(did_it_save == 2) print_message(msg_win, "Can not open the a file!");
                    else if(did_it_save == 0) print_message(msg_win, "Game saved successfully!");
                }
                continue;
            case ' ':
                attack(main_game, msg_win, level);
                /*بازی هیولا*/
                if(main_game->hero.speed_spell != 3)
                {
                room_index = is_in_monster_room(main_game, level);
                monster_counter = how_much_monster_nearby(main_game, level);
                if(monster_counter)
                {
                    monster_attack(main_game, level, msg_win, monster_counter);
                }
                else
                {
                    if(room_index)
                        monster_chase(main_game, level, room_index - 1);
                }
                }
                /**/
                break;
            case 'f':
        char direction = getch();
        switch (direction) {
            
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
        char next_step = main_game->floors[level].map[newPosition.y][newPosition.x];
        int dx = newPosition.x - main_game->hero.position.x;
        int dy = newPosition.y - main_game->hero.position.y;
                while((next_step == '.') || (next_step == '+') || (next_step == '#'))
                {
                    Point temp1 = main_game->hero.position;
                    main_game->hero.position = newPosition;
                    if(check_for_trap(main_game, level, msg_win))
                    {
                        mvaddch(newPosition.y + 3, newPosition.x, main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x]);
                        main_game->hero.position = temp1;
                        print_data(data_win, main_game->hero, level);
                        break;
                    }
                    main_game->hero.position = temp1;
                    main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x] = my_ch;
                    attron(COLOR_PAIR(5));
                    mvaddch(main_game->hero.position.y + 3, main_game->hero.position.x, my_ch);
                    attroff(COLOR_PAIR(5));
                    my_ch = main_game->floors[level].map[newPosition.y][newPosition.x];
                    main_game->floors[level].map[newPosition.y][newPosition.x] = main_game->hero.symbol;
                    attron(COLOR_PAIR(this_game_settings.hero_color));
                    mvaddch(newPosition.y + 3, newPosition.x, main_game->hero.symbol);
                    attroff(COLOR_PAIR(this_game_settings.hero_color));
                    main_game->hero.position = newPosition;
                    if(my_ch == '+' || my_ch == '#')
                    {
                        update_map(main_game, level);
                    }
                    newPosition.x += dx;
                    newPosition.y += dy;
                    next_step = main_game->floors[level].map[newPosition.y][newPosition.x];
                }
        flag = 1;
        break;
    }
    if(flag)
        continue;
    switch(main_game->floors[level].map[newPosition.y][newPosition.x])
    {
        case '+':
        case '.':
        case '#':
            Point temp1 = main_game->hero.position;
            main_game->hero.position = newPosition;
            if(check_for_trap(main_game, level, msg_win))
            {
                mvaddch(newPosition.y + 3, newPosition.x, main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x]);
                main_game->hero.position = temp1;
                print_data(data_win, main_game->hero, level);
                break;
            }
            main_game->hero.position = temp1;
            main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x] = my_ch;
            attron(COLOR_PAIR(5));
            mvaddch(main_game->hero.position.y + 3, main_game->hero.position.x, my_ch);
            attroff(COLOR_PAIR(5));
            my_ch = main_game->floors[level].map[newPosition.y][newPosition.x];
            main_game->floors[level].map[newPosition.y][newPosition.x] = main_game->hero.symbol;
            attron(COLOR_PAIR(this_game_settings.hero_color));
            mvaddch(newPosition.y + 3, newPosition.x, main_game->hero.symbol);
            attroff(COLOR_PAIR(this_game_settings.hero_color));
            main_game->hero.position = newPosition;
            if(my_ch == '+' || my_ch == '#')
            {
                 update_map(main_game, level);
            }
            /*بازی هیولا*/
            if(main_game->hero.speed_spell != 3)
            {
            room_index = is_in_monster_room(main_game, level);
            monster_counter = how_much_monster_nearby(main_game, level);
            if(monster_counter)
            {
                monster_attack(main_game, level, msg_win, monster_counter);
            }
            else
            {
                if(room_index)
                    monster_chase(main_game, level, room_index - 1);
            }
            }
            /**/
            break;
        case 'O': case 'A': case 'R': case 'C': case 'W': case 'P': case 'L':
            Point temp = main_game->hero.position;
            main_game->hero.position = newPosition;
            check_and_pick_item(main_game, level, msg_win);
            mvaddch(newPosition.y + 3, newPosition.x, main_game->floors[level].map[main_game->hero.position.y][main_game->hero.position.x]);
            main_game->hero.position = temp;
            /*بازی هیولا*/
            if(main_game->hero.speed_spell != 3)
            {
            room_index = is_in_monster_room(main_game, level);
            monster_counter = how_much_monster_nearby(main_game, level);
            if(monster_counter)
            {
                monster_attack(main_game, level, msg_win, monster_counter);
            }
            else
            {
                if(room_index)
                    monster_chase(main_game, level, room_index - 1);
            }
            }
            /**/
            break;
        case '<':
            if(level < 3){
                clear();
                refresh();
                break_point = 0;
                make_floor(main_game, level + 1, msg_win, data_win);
            }
            else{
                clear();
                refresh();
                getch();
                level = 4;
                int rows, cols;
                getmaxyx(stdscr, rows, cols);
                create_treasure_room(rows + 6, cols, main_game, level, msg_win, data_win);
            }
                break;
        case ' ':
        case '_':
        case '|':
            print_message(msg_win, "");
            break;
    }
    print_data(data_win, main_game->hero, level);
    refresh();
    }
    
}
