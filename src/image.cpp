#include "images.h"
#include "actor.h"

Image::Image()
{
    SDL_Surface* passive_animation = NULL;
    SDL_Surface* attack_animation = NULL;
    SDL_Surface* move_animation = NULL;
    int frames_per_second = 0;
    int passive_number_of_pictures = 0;
    int attack_number_of_pictures = 0;
    int move_number_of_pictures = 0;
}
Image Images[4];

void images_factory()
{
    fstream read_file;
    string work_string;
    int number_of_creatures;
    read_file.open("../bin/data/Images.txt");
    getline(read_file, work_string);
    istringstream(work_string) >> number_of_creatures;

    for(int i = 0; i < number_of_creatures; i++)
    {
        getline(read_file, work_string);
        for(int j = 0; j < 3; j++)
        {
            Images[i].animation[j] = SDL_LoadBMP(work_string.c_str());
            getline(read_file, work_string);
        }
        getline(read_file, work_string);
        istringstream(work_string) >> Images[i].frames_per_second;
        for(int j = 0; j < 3; j++)
        {
            getline(read_file, work_string);
            istringstream(work_string) >> Images[i].number_of_pictures[j];
        }
        getline(read_file, work_string);
        istringstream(work_string) >> Images[i].image_h;
        getline(read_file, work_string);
        istringstream(work_string) >> Images[i].image_w;
    }
}

void Image::draw(int i, int j, int type_of_creature, int type_of_animation, int &counter, int &mover, SDL_Surface* Screen)
{
    counter += mover;
    SDL_Rect destination;
    SDL_Rect image;
    destination.x = base_x + j*offset_x;
    destination.y = base_y + i*offset_y;
    image.h = image_h;
    image.w = image_w;
    image.x = 0;
    image.y = image_h * counter;
    SDL_BlitSurface(animation[type_of_animation], &image, Screen, &destination);
    if(counter == number_of_pictures[type_of_animation])
        mover = -1;
    if(counter == 0)
        mover = 1;
}

