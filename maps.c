#include "headers.h"

void display_game() {
    clear();
    refresh();
    curs_set(0);
    int rows, cols;
    noecho();
    getmaxyx(stdscr, rows, cols);
    rows -= 4;
    Game* main_game = calloc(1, sizeof(Game));
    for(int i = 0; i < 4; i++)
    {
        main_game->floors[i].map = create_empty_map(cols, rows);
        main_game->floors[i].height = rows;
        main_game->floors[i].width = cols;
        main_game->floors[i].room_count = rand() % 4 + 6;
        generate_random_map(&(main_game->floors[i]));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mvprintw(i + 2, j,"%c", main_game->floors[0].map[i][j]);
        }
       
    }
    int flag = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(main_game->floors[0].map[i][j] == '.')
            {
                Character hero;
                hero.position.y = i + 2;
                hero.position.x = j;
                hero.symbol = '@';
                mvprintw(hero.position.y, hero.position.x, "%c", hero.symbol);
                main_game->floors[0].map[hero.position.y - 2][hero.position.x] = hero.symbol;
                refresh();
                character_move(&hero, main_game->floors[0].map);
                flag = 1;
                break;
            }
            if(flag)
                break;
        }
    }
    
    refresh();
    curs_set(0);

    display_main_menu();
}

char** create_empty_map(int width, int height) {
    char** map = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; i++) {
        map[i] = (char*)malloc(width * sizeof(char));
        for (int j = 0; j < width; j++) {
            map[i][j] = ' ';
        }
    }
    return map;
}

void generate_random_map(Floor* my_floor) {
    int rooms_created = 0;
    int prev_door_x = -1, prev_door_y = -1;

    while (rooms_created < my_floor->room_count) {
        Room* room = &my_floor->rooms[rooms_created];

        room->width = (rand() % 5) + 6;
        room->height = (rand() % 3) + 6;
        int x = rand() % (my_floor->width - room->width);
        int y = rand() % (my_floor->height - room->height);

        if (!check_collision(x, y, my_floor, *room)) {
            add_room(my_floor, x, y, room);

            // اتصال در اولیه به اتاق قبلی
            int door_x = room->doors[0].x;
            int door_y = room->doors[0].y;
            if (rooms_created > 0) {
                add_corridor(my_floor->map, prev_door_x, prev_door_y, door_x, door_y, my_floor->width, my_floor->height);
            }
            prev_door_x = door_x;
            prev_door_y = door_y;
            rooms_created++;
        }
    }

    // اطمینان از اتصال همه‌ی درها به راهرو یا درهای دیگر
    for (int i = 0; i < my_floor->room_count; i++) {
        Room* room = &my_floor->rooms[i];
        for (int j = 0; j < room->door_count; j++) {
            Point door = room->doors[j];

            // بررسی اتصال در به راهرو
            int connected = 0;
            for (int d = 0; d < 4; d++) {
                int nx = door.x + (d == 1) - (d == 3);
                int ny = door.y + (d == 2) - (d == 0);
                if (nx >= 0 && nx < my_floor->width && ny >= 0 && ny < my_floor->height && my_floor->map[ny][nx] == '#') {
                    connected = 1;
                    break;
                }
            }

            // اگر در متصل نبود، یک راهرو جدید اضافه می‌شود
            if (!connected) {
                for (int k = 0; k < my_floor->room_count; k++) {
                    if (k == i) continue;
                    for (int l = 0; l < my_floor->rooms[k].door_count; l++) {
                        add_corridor(my_floor->map, door.x, door.y, my_floor->rooms[k].doors[l].x, my_floor->rooms[k].doors[l].y, my_floor->width, my_floor->height);
                        connected = 1;
                        break;
                    }
                    if (connected) break;
                }
            }
        }
    }
}

int check_collision(int x, int y, Floor* my_floor, Room thisRoom) {
    for (int i = y - 1; i <= y + thisRoom.height; i++) {
        for (int j = x - 1; j <= x + thisRoom.width; j++) {
            if (i < 0 || i >= my_floor->height || j < 0 || j >= my_floor->width || my_floor->map[i][j] != ' ') {
                return 1; // برخورد وجود دارد
            }
        }
    }
    return 0; // بدون برخورد
}

void add_room(Floor* my_floor, int x, int y, Room* thisRoom) {
    for (int i = y; i < y + thisRoom->height; i++) {
        for (int j = x; j < x + thisRoom->width; j++) {
            if (i == y || i == y + thisRoom->height - 1 || j == x || j == x + thisRoom->width - 1) {
                my_floor->map[i][j] = (j == x || j == x + thisRoom->width - 1) ? '|' : '_';
            }
            else {
                my_floor->map[i][j] = '.';
            }
            if((i == y && j == x) || (i == y && j == x + thisRoom->width - 1))
            {
                my_floor->map[i][j] = ' ';
            }
        }
    }
    thisRoom->door_count = rand() % 4 + 1;
    int used_walls[4] = {0, 0, 0, 0};
    for (int i = 0; i < thisRoom->door_count; i++) {
        int where;
        do {
            where = rand() % 4;
        } while (used_walls[where]); 

        used_walls[where] = 1;

        if (where == 0) { 
            thisRoom->doors[i].x = x + 1 + rand() % (thisRoom->width - 2);
            thisRoom->doors[i].y = y;
        } else if (where == 1) { 
            thisRoom->doors[i].x = x + 1 + rand() % (thisRoom->width - 2);
            thisRoom->doors[i].y = y + thisRoom->height - 1;
        } else if (where == 2) { 
            thisRoom->doors[i].x = x;
            thisRoom->doors[i].y = y + 1 + rand() % (thisRoom->height - 2);
        } else if (where == 3) { 
            thisRoom->doors[i].x = x + thisRoom->width - 1;
            thisRoom->doors[i].y = y + 1 + rand() % (thisRoom->height - 2);
        }

        my_floor->map[thisRoom->doors[i].y][thisRoom->doors[i].x] = '+';
    }

}

void add_corridor(char** map, int start_x, int start_y, int end_x, int end_y, int width, int height) {
    int visited[height][width];
    Point previous[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            visited[i][j] = 0;
            previous[i][j] = (Point){-1, -1};
        }
    }

    Queue q;
    init_queue(&q);
    enqueue(&q, start_x, start_y);
    visited[start_y][start_x] = 1;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!is_empty(&q)) {
        Point curr = dequeue(&q);

        if (curr.x == end_x && curr.y == end_y) {
            while (previous[curr.y][curr.x].x != -1 && previous[curr.y][curr.x].y != -1) {
                if (map[curr.y][curr.x] == ' ') {
                    map[curr.y][curr.x] = '#';
                }
                curr = previous[curr.y][curr.x];
            }
            return;
        }

        for (int i = 0; i < 4; i++) {
            int new_x = curr.x + directions[i][0];
            int new_y = curr.y + directions[i][1];

            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height && !visited[new_y][new_x]) {
                if (map[new_y][new_x] == ' ' || map[new_y][new_x] == '+' || map[new_y][new_x] == '#') {
                    visited[new_y][new_x] = 1;
                    previous[new_y][new_x] = curr;
                    enqueue(&q, new_x, new_y);
                }
            }
        }
    }
}

void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int is_empty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, int x, int y) {
    if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front) return; // صف پر است
    q->points[q->rear].x = x;
    q->points[q->rear].y = y;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
}

Point dequeue(Queue* q) {
    Point p = q->points[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return p;
}