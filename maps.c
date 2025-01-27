#include "headers.h"

void display_game() {
    clear();
    refresh();
    curs_set(0);
    int rows, cols;
    noecho();
    getmaxyx(stdscr, rows, cols);
    rows -= 4;
    char** first_map = create_empty_map(cols, rows);
    //getch();
    int room_count = rand() % 4 + 6;
    generate_random_map(first_map, cols, rows, room_count);
    //mvprintw(5, 5, "qqqq");
    //getch();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mvprintw(i + 2, j,"%c", first_map[i][j]);
        }
        //printw("\n");
    }
    //getch();
    refresh();
    curs_set(0);
    getch();
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

void add_room(char** map, int x, int y, int room_width, int room_height) {
    for (int i = y; i < y + room_height; i++) {
        for (int j = x; j < x + room_width; j++) {
            if (i == y || i == y + room_height - 1 || j == x || j == x + room_width - 1) {
                map[i][j] = (j == x || j == x + room_width - 1) ? '|' : '_';
            }
            else {
                map[i][j] = '.';
            }
            if((i == y && j == x) || (i == y && j == x + room_width - 1))
            {
                map[i][j] = ' ';
            }
        }
    }
    // افزودن درها روی هر چهار دیوار
    int door_positions[4][2];

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



int check_collision(char** map, int x, int y, int room_width, int room_height, int map_width, int map_height) {
    for (int i = y - 1; i <= y + room_height; i++) {
        for (int j = x - 1; j <= x + room_width; j++) {
            if (i < 0 || i >= map_height || j < 0 || j >= map_width || map[i][j] != ' ') {
                return 1; // برخورد وجود دارد
            }
        }
    }
    return 0; // بدون برخورد
}

void generate_random_map(char** map, int map_width, int map_height, int room_count) {
    int rooms_created = 0;
    int prev_door_x = -1, prev_door_y = -1;
    while (rooms_created < room_count) {
        int room_width = (rand() % 5) + 6; // عرض تصادفی (حداقل 4)
        int room_height = (rand() % 3) + 6; // ارتفاع تصادفی (حداقل 4)
        int x = rand() % (map_width - room_width);
        int y = rand() % (map_height - room_height);

        if (!check_collision(map, x, y, room_width, room_height, map_width, map_height)) {
            add_room(map, x, y, room_width, room_height);

            // پیدا کردن در برای اتصال راهرو
            int door_x = x + room_width / 2;
            int door_y = y + room_height / 2;
            for (int i = y; i < y + room_height; i++) {
                for (int j = x; j < x + room_width; j++) {
                    if (map[i][j] == '+') {
                        door_x = j;
                        door_y = i;
                    }
                }
            }

            // اتصال به اتاق قبلی
            if (rooms_created > 0) {
                add_corridor(map, prev_door_x, prev_door_y, door_x, door_y, map_width, map_height);
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