#include "headers.h"

pthread_t music_thread;  
Mix_Music *current_music = NULL;
int music_playing = 0;

/*void *play_music_background(void *arg) {
    const char *music_file = (const char *)arg;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Music *music = Mix_LoadMUS(music_file);
    if (!music) {
        printf("Error loading music: %s\n", Mix_GetError());
        return NULL;
    }

    current_music = music;
    if (Mix_PlayMusic(music, -1) == -1) {  // -1 یعنی موسیقی **بی‌نهایت بار** تکرار شود
        printf("Error playing music: %s\n", Mix_GetError());
    }
    
    music_playing = 1;
    return NULL;
}*/

void *play_music_background(void *arg) {
    const char *music_file = (const char *)arg;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Music *music = Mix_LoadMUS(music_file);
    if (!music) {
        printf("Error loading music: %s\n", Mix_GetError());
        return NULL;
    }

    current_music = music;
    if (Mix_PlayMusic(music, -1) == -1) {  // -1 یعنی موسیقی **بی‌نهایت بار** تکرار شود
        printf("Error playing music: %s\n", Mix_GetError());
    }
    
    music_playing = 1;
    return NULL;
}

void start_music(const char *music_file) {
    stop_music(); // اگر آهنگ قبلی در حال پخش است، آن را متوقف کن

    if (pthread_create(&music_thread, NULL, play_music_background, (void *)music_file) != 0) {
        printf("Failed to create music thread\n");
    }
}

void stop_music() {
    if (music_playing) {
        Mix_HaltMusic();  
        Mix_FreeMusic(current_music);
        current_music = NULL;
        music_playing = 0;
    }
}

/*void exit_game() {
    stop_music();
    endwin();  // برای بستن ncurses
    exit(0);
}*/

/*void select_music() {
    char *songs[] = {"music1.mp3", "music2.mp3", "music3.mp3"};
    int choice = 0;

    while (1) {
        clear();
        mvprintw(5, 5, "Select Background Music:");
        for (int i = 0; i < 3; i++) {
            if (i == choice) attron(A_REVERSE);
            mvprintw(7 + i, 7, "%s", songs[i]);
            if (i == choice) attroff(A_REVERSE);
        }
        mvprintw(12, 5, "Press Enter to select | Q to go back");

        int ch = getch();
        switch (ch) {
            case 'q':
                return;
            case 'w':
                choice = (choice - 1 + 3) % 3;
                break;
            case 's':
                choice = (choice + 1) % 3;
                break;
            case '\n':  // Enter key
                start_music(songs[choice]);
                return;
        }
    }
}*/
