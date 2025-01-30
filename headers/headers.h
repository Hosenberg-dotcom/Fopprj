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
#define MAX_ROOM_MONSTERS 1
#define MAX_ROOM_DOORS 4
#define MAX_FOOD 100
#define MAX_WEAPONS 200
#define MAX_SPELLS 20
#define MAX_ROOM_FOOD 2
#define MAX_ROOM_WEAPONS 1
#define MAX_ROOM_SPELLS 1
#define MAX_ROOM_GOLDS 4
#define MAX_ROOM_TRAP 2

typedef struct Point{
    int x, y;
} Point;

typedef struct Food{
    int type;
    char symbol;
    int health_care;
    int speed_raise;
    int power_raise;
    Point position;
}Food;

typedef struct Weapons{
    int type;
    char symbol;
    int damage;
    int range_type;
    int range;
    int collect_numbers;
    Point position;
}Weapons;

typedef struct Spell{
    int type;
    char symbol;
    int time_left;
    Point position;
}Spell;

typedef struct Monsters{
    int type;
    char symbol;
    int health;
    int damage;
    int move_type;
    Point position;
}Monsters;

typedef struct GoldType{
    int type;
    char symbol;
    Point position;
}GoldType;

typedef struct Character{
    Point position;
    char symbol;
    int health;
    int color;
    Food my_foods[MAX_FOOD];
    Weapons my_weapons[MAX_WEAPONS];
    Spell my_spells[MAX_SPELLS];
} Character;

typedef struct Room{
    int type;
    Point position;    
    int width, height; 
    Food room_foods[MAX_ROOM_FOOD];
    int food_count;
    Weapons room_weapons[MAX_ROOM_WEAPONS];
    int weapon_count;
    Spell room_spells[MAX_ROOM_SPELLS];  
    int spell_count;  
    Point doors[MAX_ROOM_DOORS];    
    int door_count;
    Monsters monster[MAX_ROOM_MONSTERS];
    int monster_count;
    GoldType golds[MAX_ROOM_GOLDS];
    int gold_count;
    Point trap_position[MAX_ROOM_TRAP];
    int trap_count;
} Room;

typedef struct Floor{
    Room rooms[MAX_ROOMS]; 
    int room_count;        
    char** map;           
    int width, height;  
    Point stairs_position; 
} Floor;

typedef struct Game{
    Floor floors[4];
    int gold; 
} Game;

typedef struct Queue{
    Point points[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;
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