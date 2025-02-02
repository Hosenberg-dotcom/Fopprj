void create_treasure_room(int height, int width, Game* main_game)
{
    Room room;
    room.position.x = width * 3 / 4;
    room.position.y = height * 3 / 4;
    room.monster_count = 2;
    room.trap_count = 2;
    room.gold_count = 4;
    room.width = width / 4;
    room.height = height / 4;
    /*main_game->floors[4].map = create_empty_map(width, height);
    int x = room.position.x;
    int y = room.position.y;
    for (int i = y; i < y + room.height; i++) {
        for (int j = x; j < x + room.width; j++) {
            if (i == y || i == y + room.height - 1 || j == x || j == x + room.width - 1) {
                main_game->floors[4].map[i][j] = (j == x || j == x + room.width - 1) ? '|' : '_';
            }
            else {
                main_game->floors[4].map[i][j] = '.';
            }
            if((i == y && j == x) || (i == y && j == x + room.width - 1))
            {
                main_game->floors[4].map[i][j] = ' ';
            }
        }
    }*/
    /*for(int i = 0; i < 5; i++)
    {
        room.monster[i].type = 4;
        room.monster[i].damage = 30;
        room.monster[i].health = 30;
        room.monster[i].move_left = 10;
        room.monster[i].symbol = 'U';
        room.monster[i].position = malloc(sizeof(Point));
        do
        {
            room.monster[i].position->x = room.position.x + (rand() % (room.width - 2)) + 1;
            room.monster[i].position->y = room.position.y + (rand() % (room.height - 2)) + 1;
        } while (main_game->floors[4].map[room.monster[i].position->y][room.monster[i].position->x] != '.');
        main_game->floors[4].map[room.monster[i].position->y][room.monster[i].position->x] = 'U';
        room.golds[i].symbol = 'L';
        int chance = rand() % 2;
        switch(chance)
        {
            case 0:
            room.golds[i].type = 0;
            break;
            case 1:
            room.golds[i].type = 1;
        }
        room.golds[i]
        do
        {
            room.golds[i].position.x = room.position.x + (rand() % (room.width - 2)) + 1;
            room.golds[i].position.y = room.position.y + (rand() % (room.height - 2)) + 1;
        } while (main_game->floors[4].map[room.golds[i].position.y][room.golds[i].position.x] != '.');
        main_game->floors[4].map[room.golds[i].position.y][room.golds[i].position.x] = 'L';
        do
        {
            room.trap_position->x = room.position.x + (rand() % (room.width - 2)) + 1;
            room.trap_position->y = room.position.y + (rand() % (room.height - 2)) + 1;
        } while (main_game->floors[4].map[room.trap_position->y][room.trap_position->x] != '.');
        main_game->floors[4].map[room.golds[i].position.y][room.golds[i].position.x] = '^';
    }*/
    main_game->floors[4].map = create_empty_map(width, height);
    int x = room.position.x;
    int y = room.position.y;
    for (int i = y; i < y + room.height; i++) {
        for (int j = x; j < x + room.width; j++) {
            if (i == y || i == y + room.height - 1 || j == x || j == x + room.width - 1) {
                main_game->floors[4].map[i][j] = (j == x || j == x + room.width - 1) ? '|' : '_';
            }
            else {
                main_game->floors[4].map[i][j] = '.';
            }
            if((i == y && j == x) || (i == y && j == x + room.width - 1))
            {
                main_game->floors[4].map[i][j] = ' ';
            }
        }
    }
    main_game->floors[4].height = room.height;
    main_game->floors[4].room_count = 1;
    main_game->floors[4].width = room.width;
   for(int i = 0; i < 2; i++)
   {
        room.monster[i].type = 4;
        room.monster[i].damage = 30;
        room.monster[i].health = 30;
        room.monster[i].move_left = 10;
        room.monster[i].symbol = 'U';
        room.monster[i].position = malloc(sizeof(Point));
        do
        {
            room.monster[i].position->x = room.position.x + (rand() % (room.width - 2)) + 1;
            room.monster[i].position->y = room.position.y + (rand() % (room.height - 2)) + 1;
        } while (main_game->floors[4].map[room.monster[i].position->y][room.monster[i].position->x] != '.');
        main_game->floors[4].map[room.monster[i].position->y][room.monster[i].position->x] = 'U';
        room.golds[i].symbol = 'L';
        do
        {
            room.trap_position->x = room.position.x + (rand() % (room.width - 2)) + 1;
            room.trap_position->y = room.position.y + (rand() % (room.height - 2)) + 1;
        } while (main_game->floors[4].map[room.trap_position->y][room.trap_position->x] != '.');
        main_game->floors[4].map[room.golds[i].position.y][room.golds[i].position.x] = '^';
   }
   for(int i = 0; i < 4; i++)
   {
        int chance = rand() % 2;
        switch(chance)
        {
            case 0:
            room.golds[i].type = 0;
            break;
            case 1:
            room.golds[i].type = 1;
        }
        room.golds[i];
        do
        {
            room.golds[i].position.x = room.position.x + (rand() % (room.width - 2)) + 1;
            room.golds[i].position.y = room.position.y + (rand() % (room.height - 2)) + 1;
        } while (main_game->floors[4].map[room.golds[i].position.y][room.golds[i].position.x] != '.');
        main_game->floors[4].map[room.golds[i].position.y][room.golds[i].position.x] = 'L';
   }
    main_game->floors[4].rooms[0] = room;
    do
    {
        main_game->hero.position.x = main_game->floors[4].rooms[0].position.x + (rand() % (main_game->floors[4].rooms[0].width - 2)) + 1;
        main_game->hero.position.y = main_game->floors[4].rooms[0].position.y + (rand() % (main_game->floors[4].rooms[0].height - 2)) + 1;
    } while (main_game->floors[4].rooms[0].map[main_game->hero.position.y][main_game->hero.position.x] != '.');
    main_game->floors[4].rooms[0].map[main_game->hero.position.y][main_game->hero.position.x] = main_game->hero.symbol;
    for(int i = 0; i < height; i++)
    {
        for(int j = width; j++)
        {
            mvaddch(i + 3, j, main_game->floors[4].map[i][j]);
        }
    }
    refresh();
}