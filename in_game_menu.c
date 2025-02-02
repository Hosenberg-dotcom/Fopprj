#include "headers.h"

MessageWindow* init_message_window(int width,int height, int y) {
    MessageWindow* msg_win = malloc(sizeof(MessageWindow));
    msg_win->screen_height = height;
    msg_win->width = width;
    msg_win->type = y;
    if(y == 0)
        msg_win->win = newwin(3, width, 0, 0);  // ارتفاع ۳، عرض `width`، مکان `(0,0)`
    else
        msg_win->win = newwin(3, width, height - 3, 0);
    wattron(msg_win->win, COLOR_PAIR(1));
    box(msg_win->win, 0, 0);
    wattroff(msg_win->win, COLOR_PAIR(1));
    wrefresh(msg_win->win);
    return msg_win;
}

void print_data(MessageWindow* data_win, Character hero, int level)
{
    werase(data_win->win);  // پاک کردن پنجره
    wattron(data_win->win, COLOR_PAIR(1));
    box(data_win->win, 0, 0);  // کشیدن کادر دور `window`
    wattroff(data_win->win, COLOR_PAIR(1));
    mvwprintw(data_win->win, 1, data_win->width / 8, "User: %s", this_game_settings.player_name);
    mvwprintw(data_win->win, 1, data_win->width * 3 / 8, "Health: %d",hero.health);
    mvwprintw(data_win->win, 1, data_win->width * 5 / 8, "Gold: %d",hero.gold);
    mvwprintw(data_win->win, 1, data_win->width * 7 / 8, "Level: %d",level);
    wrefresh(data_win->win);
}

void print_message(MessageWindow* msg_win, const char* msg) {
    werase(msg_win->win);  // پاک کردن پنجره
    wattron(msg_win->win, COLOR_PAIR(1));
    box(msg_win->win, 0, 0);  // کشیدن کادر دور `window`
    wattroff(msg_win->win, COLOR_PAIR(1));
    if (msg && strlen(msg) > 0) {  
        mvwprintw(msg_win->win, 1, (msg_win->width - strlen(msg)) / 2, "%s", msg);  // نمایش پیام در `window`
    }

    wrefresh(msg_win->win);  // به‌روزرسانی `window`
}

void destroy_message_window(MessageWindow* msg_win) {
    delwin(msg_win->win);
    free(msg_win);
}

void show_combined_item_menu(Game *main_game, MessageWindow* msg_win, MessageWindow* data_win, int level) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    WINDOW *background_win = newwin(rows, cols, 0, 0);
    overwrite(stdscr, background_win);

    int menu_width = cols / 3;
    int menu_height = rows - 6;
    int start_y = 3;

    WINDOW *food_win = newwin(menu_height, menu_width, start_y, 0);
    WINDOW *weapon_win = newwin(menu_height, menu_width, start_y, menu_width);
    WINDOW *spell_win = newwin(menu_height, menu_width, start_y, menu_width * 2);

    keypad(food_win, TRUE);
    keypad(weapon_win, TRUE);
    keypad(spell_win, TRUE);

    int current_menu = 0;  // 0 = غذاها | 1 = سلاح‌ها | 2 = معجون‌ها
    int highlight[3] = {0, 0, 0};

    while (1) {

        overwrite(background_win, stdscr);
        refresh();

        wattron(food_win, COLOR_PAIR(2));
        werase(food_win); box(food_win, 0, 0);
        wattroff(food_win, COLOR_PAIR(2));
        wattron(weapon_win, COLOR_PAIR(2));
        werase(weapon_win); box(weapon_win, 0, 0);
        wattroff(weapon_win, COLOR_PAIR(2));
        wattron(spell_win, COLOR_PAIR(2));
        werase(spell_win); box(spell_win, 0, 0);
        wattroff(spell_win, COLOR_PAIR(2));

        // عنوان‌ها
        wattron(food_win, COLOR_PAIR(3));
        wattron(weapon_win, COLOR_PAIR(3));
        wattron(spell_win, COLOR_PAIR(3));
        mvwprintw(food_win, 1, (menu_width - 12) / 2, "Food Inventory");
        mvwprintw(weapon_win, 1, (menu_width - 14) / 2, "Weapons Inventory");
        mvwprintw(spell_win, 1, (menu_width - 13) / 2, "Spells Inventory");
        mvwprintw(weapon_win, 3, 2, "Short range weapons:");
        mvwprintw(weapon_win, 7, 2, "Long range weapons:");
        //mvwprintw(food_win, 3, 2, "Hero Satiety: %d", main_game->hero.hunger);
        wattroff(food_win, COLOR_PAIR(3));
        wattroff(weapon_win, COLOR_PAIR(3));
        wattroff(spell_win, COLOR_PAIR(3));

        // نمایش آیتم‌ها
        int max_items[3] = {main_game->hero.food_count, main_game->hero.weapon_count, main_game->hero.spell_count};

        for (int menu = 0; menu < 3; menu++) {
            WINDOW *win = (menu == 0) ? food_win : (menu == 1) ? weapon_win : spell_win;
            int short_range_weapon_printed = 0;
            for (int i = 0; i < max_items[menu]; i++) {
                if (i == highlight[menu]) wattron(win, A_REVERSE);
                if (menu == 0) {
                    mvwprintw(win, 3 + i + 2, 2, "Food %d", i + 1);
                    if(i >= 19)
                        break;
                } else if (menu == 1) {
                    if(i == main_game->hero.selected_weapon)
                        continue;
                    if(main_game->hero.my_weapons[i].range_type == 0)
                    {
                        mvwprintw(win, 4 + short_range_weapon_printed, 2, "Weapon %d: Char: %c Damage: %d Rang: %d", short_range_weapon_printed + 1, main_game->hero.my_weapons[i].symbol, main_game->hero.my_weapons[i].damage, main_game->hero.my_weapons[i].range);
                        short_range_weapon_printed++;
                    }
                    else
                    {
                        mvwprintw(win, 8 + i, 2, "Weapon %d: Char: %c Damage: %d Rang: %d", i + 1 - short_range_weapon_printed, main_game->hero.my_weapons[i].symbol, main_game->hero.my_weapons[i].damage, main_game->hero.my_weapons[i].range);
                    }
                    //mvwprintw(win, 3 + i, 2, "Weapon %d: DMG %d", i + 1, main_game->hero.my_weapons[i].damage);
                } else {
                    /*if(i == main_game->hero.selected_spell)
                        continue;*/
                    if(main_game->hero.my_spells[i].type == 0)
                    {
                    mvwprintw(win, 3 + i, 2, "Spell %d: Spell Type: Health", i + 1);
                    }
                    else if(main_game->hero.my_spells[i].type == 1)
                    {
                    mvwprintw(win, 3 + i, 2, "Spell %d: Spell Type: Damage", i + 1);
                    }
                    else
                    {
                    mvwprintw(win, 3 + i, 2, "Spell %d: Spell Type: Speed", i + 1);
                    }
                }
                wattroff(win, A_REVERSE);
            }

            if (max_items[menu] == 0) {
                mvwprintw(win, 3, 2, "No items available.");
            }
        }

        wrefresh(food_win);
        wrefresh(weapon_win);
        wrefresh(spell_win);

        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                current_menu = (current_menu > 0) ? current_menu - 1 : 2;
                break;
            case KEY_RIGHT:
                current_menu = (current_menu < 2) ? current_menu + 1 : 0;
                break;
            case KEY_UP:
                highlight[current_menu] = (highlight[current_menu] > 0) ? highlight[current_menu] - 1 : max_items[current_menu];
                break;
            case KEY_DOWN:
                highlight[current_menu] = (highlight[current_menu] < max_items[current_menu]) ? highlight[current_menu] + 1 : 0;
                break;
            case '\n': // انتخاب آیتم
                if(current_menu == 0)
                {
                    main_game->hero.health += main_game->hero.my_foods[highlight[current_menu]].health_care;
                    main_game->hero.damage_spell = main_game->hero.my_foods[highlight[current_menu]].power_raise;
                    main_game->hero.speed_spell = main_game->hero.my_foods[highlight[current_menu]].speed_raise;
                    for(int j = highlight[current_menu]; j < main_game->hero.food_count - 1; j++)
                        {
                            main_game->hero.my_foods[j] = main_game->hero.my_foods[j + 1];
                        }
                    main_game->hero.food_count--;
                    print_data(data_win, main_game->hero, level);
                    print_message(msg_win, "You ate food!");
                }
                else if(current_menu == 1)
                {
                    if(main_game->hero.selected_weapon < 0)
                    {
                        main_game->hero.selected_weapon = highlight[current_menu];
                        print_message(msg_win, "You pick a weapon up!");
                    }
                    else
                    {
                        print_message(msg_win, "You have weapon allredy! press w to release it");
                        char ch = getch();
                        if(ch== 'w')
                            main_game->hero.selected_weapon = -1;
                    }
                }
                else if((current_menu == 2))
                {
                    if(main_game->hero.selected_spell < 0)
                    {
                        main_game->hero.spell_time_left = 10;
                        switch(main_game->hero.my_spells[highlight[current_menu]].type)
                        {
                            case 0:
                                main_game->hero.health_spell = 2;
                                break;
                            case 1:
                                main_game->hero.damage_spell = 2;
                                break;
                            case 2:
                                main_game->hero.speed_spell = 2;
                                break;
                        }
                        for(int j = highlight[current_menu]; j < main_game->hero.spell_count - 1; j++)
                        {
                            main_game->hero.my_spells[j] = main_game->hero.my_spells[j + 1];
                        }
                        main_game->hero.spell_count--;
                        main_game->hero.selected_spell = highlight[current_menu];
                        print_message(msg_win, "You used a Spell!");
                    }
                    else
                    {
                        print_message(msg_win, "You have spell allredy!");
                    }
                }
                break;
            case 'q': // ESC خروج
                delwin(food_win);
                delwin(weapon_win);
                delwin(spell_win);
                wrefresh(background_win);
                overwrite(background_win, stdscr);
                delwin(background_win);
                refresh();
                return;
        }
    }
}


