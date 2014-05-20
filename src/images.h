#ifndef IMAGES_H
#define IMAGES_H
#include <SDL.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Image
{
public:
    Image();
private:
    SDL_Surface* animation[3];
    int frames_per_second;
    int number_of_pictures[3];
    int image_h;
    int image_w;
friend void images_factory(Image Images[3]);
friend class Sunflower;
friend class Wallnut;
friend class Peashooter;
friend class Zombie;
};

#endif
