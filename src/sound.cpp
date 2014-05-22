#include "sound.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

void sound_factory(Sound_master &Sounds)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    fstream read_file;
    string work_string;
    read_file.open("../bin/data/Sounds.txt");
    getline(read_file, work_string);
    Sounds.Game_Music = Mix_LoadMUS(work_string.c_str());
    getline(read_file, work_string);
    Sounds.Lose_Sound = Mix_LoadWAV(work_string.c_str());
    getline(read_file, work_string);
    Sounds.Win_Sound = Mix_LoadWAV(work_string.c_str());
    for(int i = 0; i < 3; i++)
    {
        getline(read_file, work_string);
        Sounds.Zombie_Groan[i] = Mix_LoadWAV(work_string.c_str());
    }
    getline(read_file, work_string);
    Sounds.Zombie_Eat = Mix_LoadWAV(work_string.c_str());
    getline(read_file, work_string);
    Sounds.Peashooter_Shoot = Mix_LoadWAV(work_string.c_str());
    getline(read_file, work_string);
    Sounds.Sunflower_Sun_Spawn = Mix_LoadWAV(work_string.c_str());
}


Sound_master::Sound_master()
{
    Game_Music = NULL;
    Lose_Sound = NULL;
    Win_Sound = NULL;
    for(int i = 0; i < 3; i++)
    {
        Zombie_Groan[i] = NULL;
    }
    Zombie_Eat = NULL;
    Peashooter_Shoot = NULL;
    Sunflower_Sun_Spawn = NULL;
}

void Sound_master::start_game_music()
{
    if(Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(Game_Music, -1);
    }
}

void Sound_master::play_lose_sound()
{
    Mix_PlayChannel(-1, Lose_Sound, 0);
}

void Sound_master::play_win_sound()
{
    Mix_PlayChannel(-1, Win_Sound, 0);
}

void Sound_master::play_zombie_groan()
{
    int random;
    random = rand() % 3;
    Mix_PlayChannel(-1, Zombie_Groan[random], 0);
}

void Sound_master::play_zombie_eat()
{
    Mix_PlayChannel(-1, Zombie_Eat, 0);
}

void Sound_master::play_peashooter_shoot()
{
    Mix_PlayChannel(-1, Peashooter_Shoot, 0);
}

void Sound_master::play_sunflower_sun_spawn()
{
    Mix_PlayChannel(-1, Peashooter_Shoot, 0);
}
