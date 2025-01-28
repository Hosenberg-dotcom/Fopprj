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

typedef struct Point{
    int x, y;
} Point;

// صف برای الگوریتم BFS
typedef struct Queue{
    Point points[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

typedef struct Character{
    Point position;
    char symbol; // نماد قهرمان
} Character;
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
void add_room(char** map, int x, int y, int room_width, int room_height);
void add_corridor(char** map, int start_x, int start_y, int end_x, int end_y, int width, int height);
int check_collision(char** map, int x, int y, int room_width, int room_height, int map_width, int map_height);
void generate_random_map(char** map, int map_width, int map_height, int room_count);
void init_queue(Queue* q);
int is_empty(Queue* q);
void enqueue(Queue* q, int x, int y);
Point dequeue(Queue* q);
void character_move(Character* charecter, char** my_map);

#endif