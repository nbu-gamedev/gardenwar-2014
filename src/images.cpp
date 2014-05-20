#include "images.h"

const int base_x = 256;
const int base_y = 85;
const int offset_x = 80;
const int offset_y = 98;

Image::Image()
{
    for(int j = 0; j < 3; j++)
    {
        animation[j] = NULL;
    }
    frames_per_second = 0;
    for(int j = 0; j < 3; j++)
    {
        number_of_pictures[j] = 0;
    }
    image_h = 0;
    image_w = 0;
}

void images_factory(Image Images[3])
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
            getline(read_file, work_string);
            Images[i].animation[j] = SDL_LoadBMP(work_string.c_str());
        }
        getline(read_file, work_string);
        istringstream(work_string) >> Images[i].frames_per_second;
        for(int k = 0; k < 3; k++)
        {
            getline(read_file, work_string);
            istringstream(work_string) >> Images[i].number_of_pictures[k];
        }
        getline(read_file, work_string);
        istringstream(work_string) >> Images[i].image_h;
        getline(read_file, work_string);
        istringstream(work_string) >> Images[i].image_w;
    }
}




