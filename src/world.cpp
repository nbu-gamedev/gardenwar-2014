#include "world.h"
#include <cstdio>
const int SCREEN_WIDTH = 1380;
const int SCREEN_HEIGHT = 600;
#include <iostream>
using namespace std;

World::World(){
    game_over = NULL;
    Window = NULL;
    Background = NULL;
    ScreenSurface = NULL;
    sunSpawnTime = 15;
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
    game_over = SDL_LoadBMP("../bin/media/gameOver.bmp");
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
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_00.bmp"));
    SDL_SetColorKey(Images[1][0], SDL_TRUE, SDL_MapRGB(Images[1][0]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_01.bmp"));
    SDL_SetColorKey(Images[1][1], SDL_TRUE, SDL_MapRGB(Images[1][1]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_02.bmp"));
    SDL_SetColorKey(Images[1][2], SDL_TRUE, SDL_MapRGB(Images[1][2]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_03.bmp"));
    SDL_SetColorKey(Images[1][3], SDL_TRUE, SDL_MapRGB(Images[1][3]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_04.bmp"));
    SDL_SetColorKey(Images[1][4], SDL_TRUE, SDL_MapRGB(Images[1][4]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_05.bmp"));
    SDL_SetColorKey(Images[1][5], SDL_TRUE, SDL_MapRGB(Images[1][5]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_06.bmp"));
    SDL_SetColorKey(Images[1][6], SDL_TRUE, SDL_MapRGB(Images[1][6]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_07.bmp"));
    SDL_SetColorKey(Images[1][7], SDL_TRUE, SDL_MapRGB(Images[1][7]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_08.bmp"));
    SDL_SetColorKey(Images[1][8], SDL_TRUE, SDL_MapRGB(Images[1][8]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_09.bmp"));
    SDL_SetColorKey(Images[1][9], SDL_TRUE, SDL_MapRGB(Images[1][9]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_10.bmp"));
    SDL_SetColorKey(Images[1][10], SDL_TRUE, SDL_MapRGB(Images[1][10]->format, 255, 255, 255));
    Images[1].push_back(SDL_LoadBMP("../bin/media/Peashooter_animations/Attack_animation/frame_11.bmp"));
    SDL_SetColorKey(Images[1][11], SDL_TRUE, SDL_MapRGB(Images[1][11]->format, 255, 255, 255));
    Images[2].push_back(SDL_LoadBMP("../bin/media/Wallnut_animations/Basic_animation/frame_00.bmp"));
    SDL_SetColorKey(Images[2][0], SDL_TRUE, SDL_MapRGB(Images[2][0]->format, 255, 255, 255));
    Images[2].push_back(SDL_LoadBMP("../bin/media/Wallnut_animations/Basic_animation/frame_01.bmp"));
    SDL_SetColorKey(Images[2][1], SDL_TRUE, SDL_MapRGB(Images[2][1]->format, 255, 255, 255));
    Images[2].push_back(SDL_LoadBMP("../bin/media/Wallnut_animations/Basic_animation/frame_02.bmp"));
    SDL_SetColorKey(Images[2][2], SDL_TRUE, SDL_MapRGB(Images[2][2]->format, 255, 255, 255));
    Images[2].push_back(SDL_LoadBMP("../bin/media/Wallnut_animations/Basic_animation/frame_03.bmp"));
    SDL_SetColorKey(Images[2][3], SDL_TRUE, SDL_MapRGB(Images[2][3]->format, 255, 255, 255));
    Images[2].push_back(SDL_LoadBMP("../bin/media/Wallnut_animations/Basic_animation/frame_04.bmp"));
    SDL_SetColorKey(Images[2][4], SDL_TRUE, SDL_MapRGB(Images[2][4]->format, 255, 255, 255));
    Images[2].push_back(SDL_LoadBMP("../bin/media/Wallnut_animations/Basic_animation/frame_05.bmp"));
    SDL_SetColorKey(Images[2][5], SDL_TRUE, SDL_MapRGB(Images[2][5]->format, 255, 255, 255));
    Images[2].push_back(SDL_LoadBMP("../bin/media/Wallnut_animations/Basic_animation/frame_06.bmp"));
    SDL_SetColorKey(Images[2][6], SDL_TRUE, SDL_MapRGB(Images[2][6]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_00.bmp"));
    SDL_SetColorKey(Images[3][0], SDL_TRUE, SDL_MapRGB(Images[3][0]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_01.bmp"));
    SDL_SetColorKey(Images[3][1], SDL_TRUE, SDL_MapRGB(Images[3][1]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_02.bmp"));
    SDL_SetColorKey(Images[3][2], SDL_TRUE, SDL_MapRGB(Images[3][2]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_03.bmp"));
    SDL_SetColorKey(Images[3][3], SDL_TRUE, SDL_MapRGB(Images[3][3]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_04.bmp"));
    SDL_SetColorKey(Images[3][4], SDL_TRUE, SDL_MapRGB(Images[3][4]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_05.bmp"));
    SDL_SetColorKey(Images[3][5], SDL_TRUE, SDL_MapRGB(Images[3][5]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_06.bmp"));
    SDL_SetColorKey(Images[3][6], SDL_TRUE, SDL_MapRGB(Images[3][6]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_07.bmp"));
    SDL_SetColorKey(Images[3][7], SDL_TRUE, SDL_MapRGB(Images[3][7]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_08.bmp"));
    SDL_SetColorKey(Images[3][8], SDL_TRUE, SDL_MapRGB(Images[3][8]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_09.bmp"));
    SDL_SetColorKey(Images[3][9], SDL_TRUE, SDL_MapRGB(Images[3][9]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_10.bmp"));
    SDL_SetColorKey(Images[3][10], SDL_TRUE, SDL_MapRGB(Images[3][10]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_11.bmp"));
    SDL_SetColorKey(Images[3][11], SDL_TRUE, SDL_MapRGB(Images[3][11]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_12.bmp"));
    SDL_SetColorKey(Images[3][12], SDL_TRUE, SDL_MapRGB(Images[3][12]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_13.bmp"));
    SDL_SetColorKey(Images[3][13], SDL_TRUE, SDL_MapRGB(Images[3][13]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_14.bmp"));
    SDL_SetColorKey(Images[3][14], SDL_TRUE, SDL_MapRGB(Images[3][14]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_15.bmp"));
    SDL_SetColorKey(Images[3][15], SDL_TRUE, SDL_MapRGB(Images[3][15]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_16.bmp"));
    SDL_SetColorKey(Images[3][16], SDL_TRUE, SDL_MapRGB(Images[3][16]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_17.bmp"));
    SDL_SetColorKey(Images[3][17], SDL_TRUE, SDL_MapRGB(Images[3][17]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_18.bmp"));
    SDL_SetColorKey(Images[3][18], SDL_TRUE, SDL_MapRGB(Images[3][18]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_19.bmp"));
    SDL_SetColorKey(Images[3][19], SDL_TRUE, SDL_MapRGB(Images[3][19]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_20.bmp"));
    SDL_SetColorKey(Images[3][20], SDL_TRUE, SDL_MapRGB(Images[3][20]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_21.bmp"));
    SDL_SetColorKey(Images[3][21], SDL_TRUE, SDL_MapRGB(Images[3][21]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_22.bmp"));
    SDL_SetColorKey(Images[3][22], SDL_TRUE, SDL_MapRGB(Images[3][22]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_23.bmp"));
    SDL_SetColorKey(Images[3][23], SDL_TRUE, SDL_MapRGB(Images[3][23]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_24.bmp"));
    SDL_SetColorKey(Images[3][24], SDL_TRUE, SDL_MapRGB(Images[3][24]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_25.bmp"));
    SDL_SetColorKey(Images[3][25], SDL_TRUE, SDL_MapRGB(Images[3][25]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_26.bmp"));
    SDL_SetColorKey(Images[3][26], SDL_TRUE, SDL_MapRGB(Images[3][26]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_27.bmp"));
    SDL_SetColorKey(Images[3][27], SDL_TRUE, SDL_MapRGB(Images[3][27]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_28.bmp"));
    SDL_SetColorKey(Images[3][28], SDL_TRUE, SDL_MapRGB(Images[3][28]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_29.bmp"));
    SDL_SetColorKey(Images[3][29], SDL_TRUE, SDL_MapRGB(Images[3][29]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_30.bmp"));
    SDL_SetColorKey(Images[3][30], SDL_TRUE, SDL_MapRGB(Images[3][30]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_31.bmp"));
    SDL_SetColorKey(Images[3][31], SDL_TRUE, SDL_MapRGB(Images[3][31]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_32.bmp"));
    SDL_SetColorKey(Images[3][32], SDL_TRUE, SDL_MapRGB(Images[3][32]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_33.bmp"));
    SDL_SetColorKey(Images[3][33], SDL_TRUE, SDL_MapRGB(Images[3][33]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_34.bmp"));
    SDL_SetColorKey(Images[3][34], SDL_TRUE, SDL_MapRGB(Images[3][34]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_35.bmp"));
    SDL_SetColorKey(Images[3][35], SDL_TRUE, SDL_MapRGB(Images[3][35]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_36.bmp"));
    SDL_SetColorKey(Images[3][36], SDL_TRUE, SDL_MapRGB(Images[3][36]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_37.bmp"));
    SDL_SetColorKey(Images[3][37], SDL_TRUE, SDL_MapRGB(Images[3][37]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_38.bmp"));
    SDL_SetColorKey(Images[3][38], SDL_TRUE, SDL_MapRGB(Images[3][38]->format, 255, 255, 255));
    Images[3].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Walking_animation/frame_39.bmp"));
    SDL_SetColorKey(Images[3][39], SDL_TRUE, SDL_MapRGB(Images[3][39]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_000.bmp"));
    SDL_SetColorKey(Images[4][0], SDL_TRUE, SDL_MapRGB(Images[4][0]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_001.bmp"));
    SDL_SetColorKey(Images[4][1], SDL_TRUE, SDL_MapRGB(Images[4][1]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_002.bmp"));
    SDL_SetColorKey(Images[4][2], SDL_TRUE, SDL_MapRGB(Images[4][2]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_003.bmp"));
    SDL_SetColorKey(Images[4][3], SDL_TRUE, SDL_MapRGB(Images[4][3]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_004.bmp"));
    SDL_SetColorKey(Images[4][4], SDL_TRUE, SDL_MapRGB(Images[4][4]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_005.bmp"));
    SDL_SetColorKey(Images[4][5], SDL_TRUE, SDL_MapRGB(Images[4][5]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_006.bmp"));
    SDL_SetColorKey(Images[4][6], SDL_TRUE, SDL_MapRGB(Images[4][6]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_007.bmp"));
    SDL_SetColorKey(Images[4][7], SDL_TRUE, SDL_MapRGB(Images[4][7]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_008.bmp"));
    SDL_SetColorKey(Images[4][8], SDL_TRUE, SDL_MapRGB(Images[4][8]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_009.bmp"));
    SDL_SetColorKey(Images[4][9], SDL_TRUE, SDL_MapRGB(Images[4][9]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_010.bmp"));
    SDL_SetColorKey(Images[4][10], SDL_TRUE, SDL_MapRGB(Images[4][10]->format, 255, 255, 255));
    Images[4].push_back(SDL_LoadBMP("../bin/media/Zombie_animations/Eating_animation/frame_011.bmp"));
    SDL_SetColorKey(Images[4][11], SDL_TRUE, SDL_MapRGB(Images[4][11]->format, 255, 255, 255));
}

void World::destroyWorld(){
    SDL_DestroyWindow(Window);
    SDL_FreeSurface( game_over );
    SDL_FreeSurface(Background);
    for(int i=0; i<4; i++)
    {
        for(unsigned int j=0; j<Images[i].size(); j++)
        {
            SDL_FreeSurface(Images[i][j]);
        }
    }
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
                switch (grid[i][j]->getType())
                {
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
                    case(PEASHOOTER):
                    {
                        apply_surface((base_x + j*offset_x), (base_y + i*offset_y), Images[1][grid[i][j]->return_counter()], ScreenSurface);
                        grid[i][j]->fill_counter(grid[i][j]->return_mover());
                        if(grid[i][j]->return_counter() == 11)
                            grid[i][j]->fill_mover(-1);
                        if(grid[i][j]->return_counter() == 1)
                            grid[i][j]->fill_mover(1);
                        break;
                    }
                    case(WALLNUT):
                    {
                        apply_surface((base_x + j*offset_x), (base_y + i*offset_y), Images[2][grid[i][j]->return_counter()], ScreenSurface);
                        grid[i][j]->fill_counter(grid[i][j]->return_mover());
                        if(grid[i][j]->return_counter() == 6)
                            grid[i][j]->fill_mover(-1);
                        if(grid[i][j]->return_counter() == 1)
                            grid[i][j]->fill_mover(1);
                        break;
                    }
                    case(ZOMBIE):
                    {
                        if(grid[i][j]->getAct() == MOVE)
                        {
                            if(grid[i][j]->return_move_counter() % 8 < 4)
                            {
                                apply_surface((base_x + j*offset_x - 40 + 0.45*grid[i][j]->return_counter() ), (base_y + i*offset_y - 50), Images[3][grid[i][j]->return_counter()], ScreenSurface);
                                grid[i][j]->fill_counter(1);
                                if(grid[i][j]->return_counter() == 40)
                                    grid[i][j]->fill_counter(-40);
                            }
                            else
                            {
                                apply_surface((base_x + j*offset_x - 80 + 0.45*grid[i][j]->return_counter()), (base_y + i*offset_y - 50), Images[3][grid[i][j]->return_counter()], ScreenSurface);
                                grid[i][j]->fill_counter(1);
                                if(grid[i][j]->return_counter() == 40)
                                    grid[i][j]->fill_counter(-40);
                            }
                        }
                        if(grid[i][j]->getAct() == ATTACK)
                        {
                            apply_surface((base_x + j*offset_x), (base_y + i*offset_y), Images[4][grid[i][j]->return_counter()], ScreenSurface);
                            grid[i][j]->fill_counter(1);
                        }
                    }
                }
            }
        }
    }
    SDL_UpdateWindowSurface(Window);
}

void World::update(){
     for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(grid[i][j] != NULL){
                // vreme za umirane:
                if((grid[i][j]->getHP())<=0){
                  //  if(grid[i][j]->getAct()!=DIE) {grid[i][j]->setAct(DIE);}
                    //else {//if(grid[i][j]->timeToAct()){ // ... && grid[i][j]->getAct()==DIE
                        delete grid[i][j];
                        grid[i][j]=NULL;
                        continue;
                 //   }
                }
                // ako e zombie:
                if (grid[i][j]->getType()==ZOMBIE){
                    if(j==0){  //  1. stignalo e do kraq
                        if (grid[i][j]->timeToAct()){
                            gameOver();
                        }
                    }
                    else if (grid[i][j-1]==NULL) { //  2. mesti se
                        if(grid[i][j]->timeToAct()) {
                            grid[i][j-1]=grid[i][j];
                            grid[i][j]=NULL;
                            grid[i][j-1]->setAct(MOVE);
                        }
                    }
                    else if (grid[i][j-1]->getType()!=ZOMBIE){// 3. ima cvete otpred
                        grid[i][j-1]->setHP(-(grid[i][j]->getDamage()));
                        if(grid[i][j]->getAct()!=ATTACK){
                            grid[i][j]->setAct(ATTACK);
                        }
                    }
                }
                // ako e cvete:
                else {
                   if (grid[i][j]->getType()==PEASHOOTER){
                        for(int k=j+1;k<M;k++){
                            if(grid[i][k]!=NULL){
                                if (grid[i][k]->getType()==ZOMBIE && (grid[i][k]->getAct()!=DIE)){
                                    grid[i][k]->setHP(-(grid[i][j]->getDamage()));
                                  //  if(grid[i][j]->getAct()!=ATTACK) { grid[i][j]->setAct(ATTACK);}
                                    break;
                                }
                            }
                        }
                    }
                    /*else if (grid[i][j]->getType()==SUNFLOWER){
                            //puska Sun...

                    }

                    */
                }
                if (grid[i][j]!=NULL) grid[i][j]->incCounter();
            }
        }
    }
}

void World::gameOver(){
    apply_surface(380, 190, game_over, ScreenSurface);
    SDL_UpdateWindowSurface(Window);
    SDL_Delay(1500);
    quit=true;
}

void World::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void World::createSun() {
    //placing new sun in the vector "suns" in world.
    suns.push_back(new Sun(rand() %gridSizeX + gridStartX , rand() %gridSizeY + gridStartY));
    cout << "Puting sun in vector. Total suns: " << suns.size() <<  endl;
}

void World::createPeashooter(SDL_Event event){
    int row = 0;
    int column = 0;

    // Place Peashooter at clicked grid location
    column = (event.button.x - base_x)/offset_x;
    row = (event.button.y - base_y)/offset_y;
    cout << "column:" << column << " row:" << row << " address:"
    << grid[row][column] << endl; //6te mahna testovete kato sam naprava i Sun.

    if (grid[row][column] == NULL) {
        grid[row][column] = new Peashooter();
        cout << "Placed new peashooter" << endl; //6te mahna testovete kato sam naprava i Sun.
    }
}
