#ifndef HEADERS_H
#define HEADERS_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 1000
#define MAX_ITEMS 10
#define MAX_ROOMS 50
#define MAX_FLOORS 4
#define MAX_MONSTERS 1
#define MAX_DOORS 4

typedef struct Point{
    int x, y;
} Point;

typedef struct Item{
    char name[20]; // نام آیتم یا دشمن
    char symbol;     // نوع (مثلاً 'W' برای سلاح، 'T' برای تله، 'E' برای دشمن)
    struct Point position; // موقعیت در اتاق
} Item;


// صف برای الگوریتم BFS
typedef struct Queue{
    Point points[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

typedef struct Character{
    Point position;
    char symbol;
    int health;
} Character;

typedef struct Room{
    Point position;    // موقعیت اتاق در نقشه
    int width, height; // ابعاد اتاق
    Item items[MAX_ITEMS]; // آیتم‌ها، تله‌ها و دشمنان در اتاق
    int item_count;     // تعداد آیتم‌ها
    Point doors[MAX_DOORS];     // موقعیت درها (حداکثر 4 در)
    int door_count;
    Character monsters[MAX_MONSTERS];
} Room;

typedef struct Floor{
    Room rooms[MAX_ROOMS]; // اتاق‌های هر طبقه
    int room_count;        // تعداد اتاق‌ها
    char** map;           // نقشه‌ی طبقه
    int width, height;    // ابعاد نقشه
} Floor;

typedef struct Game{
    Floor floors[4];
    int gold; 
} Game;
// Function prototypes
void display_main_menu();
void guest_menu();
void login_menu();
void sign_in_menu();
void score_table_menu();
void settings_menu();
void set_difficulty();
void change_character_color();
void choose_hero();
void select_music();
void exit_game();
void display_loading_bar();
int regex_match();
void display_game();
char** create_empty_map(int width, int height);
void add_room(Floor* my_floor, int x, int y, Room* thisRoom);
void add_corridor(char** map, int start_x, int start_y, int end_x, int end_y, int width, int height);
int check_collision(int x, int y, Floor* my_floor, Room thisRoom);
void generate_random_map(Floor* my_floor);
void init_queue(Queue* q);
int is_empty(Queue* q);
void enqueue(Queue* q, int x, int y);
Point dequeue(Queue* q);
void character_move(Character* charecter, char** my_map);

#endif