#include "world.h"
#include <cstdio>
const int SCREEN_WIDTH = 1380;
const int SCREEN_HEIGHT = 600;
const int base_x = 256;
const int base_y = 85;
const int offset_x = 80;
const int offset_y = 98;

World::World(){
    game_over = NULL;
    Window = NULL;
    Background = NULL;
    ScreenSurface = NULL;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            grid[i][j] = NULL;
        }
    }
}

World::~World(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
                delete grid[i][j];
        }
    }
}

void World::createWorld(){
    SDL_Init(SDL_INIT_EVERYTHING);
    Window = SDL_CreateWindow("Plants Vs Zombies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ScreenSurface = SDL_GetWindowSurface(Window);
    Background = SDL_LoadBMP("../bin/media/background.bmp");
    SDL_BlitSurface(Background, NULL, ScreenSurface, NULL);
    SDL_UpdateWindowSurface(Window);
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_00.bmp"));
    SDL_SetColorKey(Images[0][0], SDL_TRUE, SDL_MapRGB(Images[0][0]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_01.bmp"));
    SDL_SetColorKey(Images[0][1], SDL_TRUE, SDL_MapRGB(Images[0][1]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_02.bmp"));
    SDL_SetColorKey(Images[0][2], SDL_TRUE, SDL_MapRGB(Images[0][2]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_03.bmp"));
    SDL_SetColorKey(Images[0][3], SDL_TRUE, SDL_MapRGB(Images[0][3]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_04.bmp"));
    SDL_SetColorKey(Images[0][4], SDL_TRUE, SDL_MapRGB(Images[0][4]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_05.bmp"));
    SDL_SetColorKey(Images[0][5], SDL_TRUE, SDL_MapRGB(Images[0][5]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_06.bmp"));
    SDL_SetColorKey(Images[0][6], SDL_TRUE, SDL_MapRGB(Images[0][6]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_07.bmp"));
    SDL_SetColorKey(Images[0][7], SDL_TRUE, SDL_MapRGB(Images[0][7]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_08.bmp"));
    SDL_SetColorKey(Images[0][8], SDL_TRUE, SDL_MapRGB(Images[0][8]->format, 255, 255, 255));
    Images[0].push_back(SDL_LoadBMP("../bin/media/Sunflower_animations/Animation_basic/frame_09.bmp"));
    SDL_SetColorKey(Images[0][9], SDL_TRUE, SDL_MapRGB(Images[0][9]->format, 255, 255, 255));
}

void World::destroyWorld(){
    SDL_DestroyWindow(Window);
    SDL_FreeSurface( game_over );
    SDL_FreeSurface(Background);
}

void World::draw()
{
    SDL_BlitSurface(Background, NULL, ScreenSurface, NULL);
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(grid[i][j] != NULL)
            {
                switch(grid[i][j]->getType())
                case(SUNFLOWER):
                {
                    apply_surface((base_x + j*offset_x), (base_y + i*offset_y), Images[0][grid[i][j]->return_counter()], ScreenSurface);
                    grid[i][j]->fill_counter(grid[i][j]->return_mover());
                    if(grid[i][j]->return_counter() == 9)
                        grid[i][j]->fill_mover(-1);
                    if(grid[i][j]->return_counter() == 1)
                        grid[i][j]->fill_mover(1);
                    break;
                }
            }
        }
    }
    SDL_UpdateWindowSurface(Window);
}

void World::update(){}

void World::gameOver(){
    apply_surface(0, 0, game_over, ScreenSurface);
    quit=true;
}

void World::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}

