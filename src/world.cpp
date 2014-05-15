#include "world.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define SCREEN_WIDTH 1380
#define SCREEN_HEIGHT 600
using namespace std;

list<Actor*>::iterator it;
list<Actor*>::iterator it2;
list<Pea*>::iterator itPea;

World::World(){
	peaImagePH = NULL;
	sunImagePH = NULL;
	shopSprite = NULL;
	numbersSpite = NULL;
    game_over = NULL;
    Window = NULL;
    Background = NULL;
    ScreenSurface = NULL;
    peaSpeed = 0;
    peaDrawSpeed = 0;
    sunSpawnTime = 5; // it saves time whale testing, should be 15 change it if its bothering you.
    sunCurrency = 50;
    apply_surface_pointer = &World::apply_surface;
    //init the shop struct
    ShopItem[PEASHOOTER].cost = 100;
    ShopItem[SUNFLOWER].cost = 50;
    ShopItem[WALLNUT].cost = 50;
    for (int i = 0; i<ALL_SHOP_ITEMS; i++){
        ShopItem[i].x = 15+(70*i);
        ShopItem[i].y = 15;
        ShopItem[i].sideX = ShopItem[i].x + 65;
        ShopItem[i].bottomY = ShopItem[i].y + 90;
        ShopItem[i].clicked = false;
    }
}

World::~World(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            for(it=grid[i][j].begin();it!=grid[i][j].end();it++) {
                delete (*it);
            }
        }
    }

    for(itPea=peas.begin();itPea!=peas.end();itPea++) {
		delete (*itPea);
    }
}
void World::readData(){
    // zombie waves
    ifstream zombiesFile("../bin/data/zombieWave.txt");
    if (!zombiesFile.fail()){
        string s;
        while(getline(zombiesFile,s)){
            istringstream ss(s);
            int sec,pos;
            ss>>sec;
            char buf;
            ss>>buf; // ':' (??)
            while(ss>>pos){
                if (pos<=300) zombieWaves[sec].push_back(pos);
            }
        }
    }
    zombiesFile.close();
    // pea speed
     ifstream peaFile("../bin/data/peaSpeed.txt");
    if (!peaFile.fail()){
        string s;
        getline(peaFile,s);
        istringstream ss(s);
        char buf;
        int spd;
        while (ss>>buf) {
            if(buf==':') {ss>>spd;break;}
        }
        peaSpeed = spd;
        peaDrawSpeed = peaSpeed/10;
    }
    peaFile.close();
}

void World::createWorld(){
    SDL_Init(SDL_INIT_EVERYTHING);
    readData();
    Window = SDL_CreateWindow("Plants Vs Zombies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ScreenSurface = SDL_GetWindowSurface(Window);
    Background = SDL_LoadBMP("../bin/media/background.bmp");
    game_over = SDL_LoadBMP("../bin/media/gameOver.bmp");
    SDL_BlitSurface(Background, NULL, ScreenSurface, NULL);
    SDL_UpdateWindowSurface(Window);
    sunImagePH = SDL_LoadBMP("../bin/media/sun.bmp");
    SDL_SetColorKey(sunImagePH, SDL_TRUE, SDL_MapRGB(sunImagePH->format, 255, 255, 255));
    if ( sunImagePH == NULL){ cout<<"Loading sun failed!!!"<< endl; }
    numbersSpite= SDL_LoadBMP("../bin/media/numberSpite.bmp");
    if ( numbersSpite == NULL){ cout<<"Loading numberSpite failed!!!"<< endl; }
    shopSprite= SDL_LoadBMP("../bin/media/shopSprite.bmp");
    if ( shopSprite == NULL){ cout<<"Loading shopSprite failed!!!"<< endl; }
    peaImagePH = SDL_LoadBMP("../bin/media/pea.bmp");
    SDL_SetColorKey(peaImagePH, SDL_TRUE, SDL_MapRGB(peaImagePH->format, 255, 255, 255));
    if ( peaImagePH == NULL){ cout<<"Error!/.../"<< endl; }
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
    SDL_FreeSurface(peaImagePH);
    SDL_FreeSurface(sunImagePH);
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
            for(it=grid[i][j].begin();it!=grid[i][j].end();it++)
            {
				if((*it)->getAct() != ATTACK)// || (*it)->getType() == PEASHOOTER)
                {
                    (*it)->draw_self(j, i, Images[(*it)->getType()][(*it)->return_counter()], ScreenSurface, *apply_surface_pointer);
                }
                else
                {
                    apply_surface((base_x + j*offset_x), (base_y + i*offset_y- 50), Images[4][(*it)->return_counter()], ScreenSurface);
                    (*it)->fill_counter(1);
                    if ((*it)->return_counter() == 12)
                        (*it)->fill_counter(-12);
                }
            }
        }
    }
    // Samir's part:
    for (unsigned int currentSun = 0; currentSun < suns.size(); currentSun++){

        apply_surface(suns[currentSun]->getX(),suns[currentSun]->getY(),sunImagePH,ScreenSurface);
    }
    //using sprite sheet for the numbers 0-9
    SDL_Rect source;
    SDL_Rect destination;
    source.y = 0;
    source.w = 18;
    source.h = 20;
    destination.y = 20;
    int number;
    int digitNumber=0; // used to know witch digit we are getting from right to left.
    int sunCurrencyTMP = sunCurrency;
    //do loop extracts the right digit and prints it on the screen,
    //uses the remaining numbers to extra the right digit and to print it
    //left of the first digit extracted;
    do{
        number = sunCurrencyTMP % 10;
        source.x = 2+(16*number);
        destination.x = 1100-(18*digitNumber); // digits printed from right to left.
        digitNumber++;
        sunCurrencyTMP = sunCurrencyTMP / 10;

    SDL_BlitSurface(numbersSpite, &source, ScreenSurface, &destination);
    } while (sunCurrencyTMP>0);



    for (int i = 0; i < ALL_SHOP_ITEMS; i++){
        destination.x = ShopItem[i].x;
        source.x = 35+(70*i);
        destination.y = 15;
        source.y = 130;
        source.w = 65;
        source.h = 90;
        int x,y;
        SDL_GetMouseState(&x,&y);

        // if Shopitem[i] noMoney draw no money img
        if ( ShopItem[i].cost > sunCurrency ){
            source.y = 316;
        }
        // if shopitem[i] clicked 95%


        // if shopiteem[i] mouseOver draw 105%
        else if (ShopItem[i].mouseOver()){
            destination.x -= 2;
            source.x += i*2;
            source.y += 92;
            source.w += 2;
            source.h += 2;
        }
        // else draw normal

        SDL_BlitSurface(shopSprite, &source, ScreenSurface, &destination);
    }


	 //Kari:
	for(itPea=peas.begin();itPea!=peas.end();itPea++) {
		apply_surface(((*itPea)->x + (*itPea)->br), offset_y*((*itPea)->y)+gridStartY, peaImagePH, ScreenSurface);
		(*itPea)->br+=peaDrawSpeed;
    }
	// ----------

    SDL_UpdateWindowSurface(Window);
}

void World::update(int clock){

	for(itPea=peas.begin();itPea!=peas.end();itPea++) {
		(*itPea)->move(peaSpeed);
    }
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
		    it=grid[i][j].begin();
            while(it!=grid[i][j].end()){

		// --- vreme za umirane:
				if( (*it)->getHP() <=0){
					if((*it)->getAct()!=DIE) {(*it)->setAct(DIE);}
					else if( (*it)->timeToAct() ){ // ... && (*it)->getAct()==DIE
						delete (*it);
						it=grid[i][j].erase(it);
					}
					else { (*it)->incCounter(); it++;}
					continue;
				}
		//---------------------

		// I. ako e zombie:
				if ( (*it)->getType()==ZOMBIE){

					bool flowerExists = false;
					Actor* enemy=grid[i][j].front();
           // 1. atakuva (enemy na sy6toto kvadrat4e)
					if( ((enemy->getType())!=ZOMBIE) && (enemy->getAct()!=DIE) ) {
						flowerExists = true;
						enemy->addHP( -((*it)->getDamage()) );
						if( (*it)->getAct()!=ATTACK){
							(*it)->setAct(ATTACK);
						}
					}
					if(!flowerExists){
			//  2. stignalo e do kraq
						if(j==0){
							if ((*it)->timeToAct()){
								gameOver();
                                break;
							}
						}
			//  3. mesti se
						else {  //  j!=0

						// 3.1. dosega se e dvijelo; prodyljava dvijenie
							if( (*it)->timeToAct()) {
								(*it)->setAct(MOVE);
								grid[i][j-1].push_back((*it));
								it=grid[i][j].erase(it);
								continue; //za da prodylji s novata stoinost na it..
							}
						//3.2 dosega e atakuvalo
							else if ((*it)->getAct()!=MOVE){
								(*it)->setAct(MOVE);
								it++;
								continue; //za da ne increase-ne counter na (*it), ot 0 na 1 i da propusne stypka
							}
							else{}
						}
					}
				}
	// II. ako e cvete:
				else {
					if ((*it)->getType()==PEASHOOTER){
                        bool zombieExists = false;
            // 1. ako ima pred nego v sy6toto kvadrat4e, no ne strelq :
                        for((it2=it)++; it2!=grid[i][j].end(); it2++){ //it2 =it+1 za da po4ne da gleda sled nego (cveteto vinagi e na pyrvo mqsto i e !)
                            if ( ((*it2)->getType()==ZOMBIE) && ((*it2)->getAct()!=DIE) ) {
                                zombieExists = true;
                                if((*it)->getAct()==STAY || (*it)->timeToAct()){
                                    (*it2)->addHP(-((*it)->getDamage()) );
                                    if((*it)->getAct()!=ATTACK) {(*it)->setAct(ATTACK);}
                                }
                                break; // namerilo e enemy, spira da tyrsi
                            }
                        }
                        if(!zombieExists){
        // 2. tyrsi v predni kvadrat4eta i strelq
                            for(int k=j+1;(k<M);k++){
                                for(it2=grid[i][k].begin(); it2!=grid[i][k].end(); it2++){
                                    if ( ((*it2)->getType()==ZOMBIE) && ((*it2)->getAct()!=DIE) ){
                                        zombieExists =true;
                                        if((*it)->getAct()==STAY || (*it)->timeToAct()){
                                    // grah4eta
                                            peas.push_back(new Pea( (*it)->getPosX(), i, *it2 ));
                                    // --------
                                            (*it2)->addHP(-((*it)->getDamage()) );
                                            if((*it)->getAct()!=ATTACK) {(*it)->setAct(ATTACK);}
                                        }
                                        break; // break na obhojdaneto na teku6toto kvadrat4e
                                    }
                                }
                                if(zombieExists) break; // namerilo e enemy, spira da tyrsi
                            }
                        }
                        // ako ve4e ne napada:
                        if(!zombieExists && (*it)->getAct()==ATTACK) {(*it)->setAct(STAY);}
					}
					else if ((*it)->getType()==SUNFLOWER){
						if((*it)->timeToAct()) {
							suns.push_back(new Sun( (gridStartX+((j+1)*offset_x)-20),(gridStartY+((i+1)*offset_y)-SUN_SIZE) ));
						}
					}
					else{}
				}
				(*it)->incCounter();
				it++;
			}
		}
	}
	itPea=peas.begin();
	while(itPea!=peas.end()) {

		if ((*itPea)->enemyIsDead()) {(*itPea)->aim=NULL;}

		// ako: 1) grah4eto e stignalo zombito 2) grah4eto e stignalo do kraq na grida
		if ( (*itPea)->reachedAim() || ((*itPea)->getPlace() > M) ) {
			delete (*itPea);
			itPea=peas.erase(itPea);
		}
		else itPea++;
    }

    clock = (clock/1000)%300;
    if(!zombieWaves[clock].empty()){
        for(unsigned int i=0; i<zombieWaves[clock].size(); i++){
            grid[(zombieWaves[clock][i])][M-1].push_back(new Zombie());
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
    cout << "Total suns: " << suns.size() <<  endl;
}

void World::createPeashooter(SDL_Event event){
    int row = 0;
    int column = 0;

    // Place Peashooter at clicked grid location
    column = (event.button.x - base_x)/offset_x;
    row = (event.button.y - base_y)/offset_y;
 //   cout << "column:" << column << " row:" << row << " address:"
 //   << grid[row][column] << endl; //6te mahna testovete kato sam naprava i Sun.

    if ((grid[row][column].empty()) || ((grid[row][column].front()->getType() == ZOMBIE))) {
            grid[row][column].push_front (new Peashooter(column));
        cout << "Placed new peashooter" << endl; //6te mahna testovete kato sam naprava i Sun.
    }
}

bool ItemsInShop::mouseOver(){
    int mouseX,mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    if ( (mouseX > x) && (mouseX < sideX) &&
         (mouseY > y) && (mouseY < bottomY)){
        return true;
    }else
        return false;
}
