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
#include <wchar.h>
#include <locale.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_QUEUE_SIZE 1000
#define MAX_ITEMS 10
#define MAX_ROOMS 50
#define MAX_FLOORS 5
#define MAX_ROOM_MONSTERS 2
#define MAX_ROOM_DOORS 4
#define MAX_FOOD 200
#define MAX_WEAPONS 200
#define MAX_SPELLS 20
#define MAX_ROOM_FOOD 2
#define MAX_ROOM_WEAPONS 3
#define MAX_ROOM_SPELLS 1
#define MAX_ROOM_GOLDS 4
#define MAX_ROOM_TRAP 2
#define MAX_PLAYER_NAME_LENGTH 30

extern struct this_game_setups this_game_settings;
extern pthread_t music_thread;  
extern Mix_Music *current_music;
extern int music_playing;

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
    //int time_left;
    Point position;
}Spell;

typedef struct Monsters{
    int type;
    char symbol;
    int health;
    int damage;
    int move_left;
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
    int gold;
    Food my_foods[MAX_FOOD];
    int food_count;
    Weapons my_weapons[MAX_WEAPONS];
    int weapon_count;
    int selected_weapon;
    Spell my_spells[MAX_SPELLS];
    int spell_count;
    int selected_spell;
    int spell_time_left;
    int health_spell;
    int speed_spell;
    int damage_spell;
} Character;

typedef struct Room{
    int type; //صفر معمولی یک کابوس دو گنج
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
    int printed_map[200][200]; 
    int show_full_map;
} Floor;

/*typedef struct Treasur_room{
    Point position;
    int width, height;
    Monsters monster[5];
    int monster_count;
    GoldType golds[5];
    int gold_count;
    Point trap_position[5];
    int trap_count;
    char** map;
}Treasur_room;*/

typedef struct Game{
    Floor floors[5];
    Character hero;
    //Room treaser_room;
} Game;

typedef struct Queue{
    Point points[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

typedef struct MessageWindow{
    int width;
    int screen_height;
    int type;
    WINDOW* win;
} MessageWindow;

typedef struct this_game_setups{
    int difficulty;
    int hero_color;
    char hero_symbol;
    char player_name[MAX_PLAYER_NAME_LENGTH];
}this_game_setups;
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
void character_move(Game* main_game, MessageWindow* msg_win,MessageWindow* data_win, int level);
void add_items_to_rooms(Floor* my_floor, int floor_index);
MessageWindow* init_message_window(int width,int height, int y);
void print_message(MessageWindow* msg_win, const char* msg);
void destroy_message_window(MessageWindow* msg_win);
Character creat_hero(int health, char symbol, int color, int gold, int food_count, int weapon_count, int spell_count);
void print_data(MessageWindow* data_win, Character hero, int level);
void print_room(Game* main_game, int level);
void print_corridors(Game* main_game, int level);
void toggle_map_display(Game* main_game, int level);
void update_map(Game* main_game, int level);
int check_item(int* perv_y, int* perv_x, int perv_Index, int y, int x);
void check_and_pick_item(Game* main_game, int level, MessageWindow* msg_win);
int check_for_trap(Game* main_game, int level, MessageWindow* msg_win);
void *play_music_background(void *arg);
void *play_music_background(void *arg);
void start_music(const char *music_file);
void stop_music();
void make_floor(Game* main_game, int level, MessageWindow* msg_win, MessageWindow* data_win);
int how_much_monster_nearby(Game* main_game, int level);
void monster_attack(Game *main_game, int level, MessageWindow *msg_win, int monster_near);
void monster_chase(Game *main_game, int level, int room_index);
int is_in_monster_room(Game *main_game, int level);
int pass_finding(Point* start, Point* destination, Game* main_game, int level);
void show_combined_item_menu(Game *main_game, MessageWindow* msg_win, MessageWindow* data_win, int level);
void speed_spell(Game* main_game);
void health_speed(Game* main_game, int* last_health);
void damage_spell(Game* main_game);
void attack(Game* main_game, MessageWindow* msg_win, int level);
void attack_melee(Game* main_game, int level, MessageWindow* msg_win);
void remove_dead_monsters(Game* main_game, int level);
void attack_ranged(Game* main_game, int level, MessageWindow* msg_win);
void check_projectile_hit(Game* main_game, int level, int dy, int dx, MessageWindow* msg_win);
void remove_weapon_if_empty(Character* hero, MessageWindow* msg_win);
void find_and_put_down_weapon(Game* main_game, int level, Point position, MessageWindow* msg_win);
void hit_monster(Game* main_game, int level, MessageWindow* msg_win, Point position);
void create_treasure_room(int height, int width, Game* main_game);
int save_game(Game* main_game, int level);
int load_game(Game* main_game, int* level);
void resume_game();
int does_save_exist();
void close_all_ncurses_windows();

#endif