#ifndef SOUND_H
#define SOUND_H
#include <SDL_mixer.h>

class Sound_master
{
public:
    Sound_master();
    void start_game_music();
    void play_win_sound();
    void play_lose_sound();
    void play_zombie_groan();
    void play_zombie_eat();
    void play_peashooter_shoot();
    void play_sunflower_sun_spawn();
private:
    Mix_Music* Game_Music;
    Mix_Chunk* Lose_Sound;
    Mix_Chunk* Win_Sound;
    Mix_Chunk* Zombie_Groan[3];
    Mix_Chunk* Zombie_Eat;
    Mix_Chunk* Peashooter_Shoot;
    Mix_Chunk* Sunflower_Sun_Spawn;
friend void sound_factory(Sound_master Sounds);
};


#endif
