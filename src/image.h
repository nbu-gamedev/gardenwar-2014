#ifndef IMAGES_H
#define IMAGES_H
#include <SDL.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
#define Y 9
class Image
{
public:
    Image();
    void draw();
private:
    SDL_Surface* passive_animation;
    SDL_Surface* attack_animation;
    SDL_Surface* move_animation;
    int frames_per_second;
    int passive_number_of_pictures;
    int attack_number_of_pictures;
    int move_number_of_pictures;
friend void images_factory();
};

void images_factory();

#endif
