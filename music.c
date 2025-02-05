#include "headers.h"

pthread_t music_thread;  
Mix_Music *current_music = NULL;
int music_playing = 0;

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
    if (Mix_PlayMusic(music, -1) == -1) { 
        printf("Error playing music: %s\n", Mix_GetError());
    }
    
    music_playing = 1;
    return NULL;
}

void start_music(const char *music_file) {
    stop_music(); 

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