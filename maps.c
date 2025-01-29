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
        //printw("\n");
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
    //getch();
    refresh();
    curs_set(0);
    //getch();
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
    /*int door_positions[4][2];

    // بالا
    door_positions[0][0] = x + 1 + rand() % (room_width - 2);
    door_positions[0][1] = y;

    // پایین
    door_positions[1][0] = x + 1 + rand() % (room_width - 2);
    door_positions[1][1] = y + room_height - 1;

    // چپ
    door_positions[2][0] = x;
    door_positions[2][1] = y + 1 + rand() % (room_height - 2);

    // راست
    door_positions[3][0] = x + room_width - 1;
    door_positions[3][1] = y + 1 + rand() % (room_height - 2);

    for (int i = 0; i < 4; i++) {
        map[door_positions[i][1]][door_positions[i][0]] = '+';
    }*/

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
            // مسیر پیدا شد
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
                if (map[new_y][new_x] == ' ' || map[new_y][new_x] == '+') {
                    visited[new_y][new_x] = 1;
                    previous[new_y][new_x] = curr;
                    enqueue(&q, new_x, new_y);
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

void generate_random_map(Floor* my_floor) {
    int rooms_created = 0;
    int prev_door_x = -1, prev_door_y = -1;
    for(int l = 0; rooms_created < my_floor->room_count; l++) {
        my_floor->rooms[l].width = (rand() % 5) + 6; // عرض تصادفی (حداقل 4)
        my_floor->rooms[l].height = (rand() % 3) + 6; // ارتفاع تصادفی (حداقل 4)
        int x = rand() % (my_floor->width - my_floor->rooms[l].width);
        int y = rand() % (my_floor->height - my_floor->rooms[l].height);

        if (!check_collision(x, y, my_floor, my_floor->rooms[l])) {
            add_room(my_floor, x, y, &(my_floor->rooms[l]));

            // پیدا کردن در برای اتصال راهرو
            int door_x = x + my_floor->rooms[l].width / 2;
            int door_y = y + my_floor->rooms[l].height / 2;
            for (int i = y; i < y + my_floor->rooms[l].height; i++) {
                for (int j = x; j < x + my_floor->rooms[l].width; j++) {
                    if (my_floor->map[i][j] == '+') {
                        door_x = j;
                        door_y = i;
                    }
                }
            }

            // اتصال به اتاق قبلی
            if (rooms_created > 0) {
                add_corridor(my_floor->map, prev_door_x, prev_door_y, door_x, door_y, my_floor->width, my_floor->height);
            }

            // ذخیره در برای اتصال بعدی
            prev_door_x = door_x;
            prev_door_y = door_y;

            rooms_created++;
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