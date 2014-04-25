#include "world.h"
#include <iostream>
#include <cstdio>
World::World(){
    background= NULL;
    screen = NULL;
    images[ZOMBIE] = NULL;
    images[PEASHOOTER] = NULL;
    images[WALLNUT] = NULL;
    gScreenSurface = NULL;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            grid[i][j] = NULL;
        }
    }
}

World::~World(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(grid[i][j] != NULL){
                delete grid[i][j];
                    std::cout<<"DESTRUCTED!!!!\n";
                }
            }
        }
}


void World::createWorld(){
       if( SDL_Init( SDL_INIT_EVERYTHING )<0) {
            printf("Error: %s\n", SDL_GetError());
       }
        //bool success = true;
        //Set up screen
        screen = SDL_CreateWindow( "Plants vs Zombies", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (screen==NULL)
            printf("Error: %s\n", SDL_GetError());

        gScreenSurface = SDL_GetWindowSurface(screen);
         if (gScreenSurface==NULL) {
                printf("Error: %s\n", SDL_GetError());
         }
        background = SDL_LoadBMP( "../bin/media/background.bmp" );
         if (background==NULL) {
                printf("Error: %s\n", SDL_GetError());
         }
        images[ZOMBIE] = SDL_LoadBMP("../bin/media/zombie.bmp");
         if (images[ZOMBIE]==NULL) {
                printf("Error: %s\n", SDL_GetError());
         }
        SDL_SetColorKey(images[ZOMBIE], SDL_TRUE, SDL_MapRGB(images[ZOMBIE]->format, 255, 255, 255));

        images[PEASHOOTER] = SDL_LoadBMP("../bin/media/peashooter.bmp");
         if (images[PEASHOOTER]==NULL) {
                printf("Error: %s\n", SDL_GetError());
         }
        SDL_SetColorKey(images[PEASHOOTER], SDL_TRUE, SDL_MapRGB(images[PEASHOOTER]->format, 255, 255, 255));

        images[WALLNUT] = SDL_LoadBMP("../bin/media/Wallnut.bmp");
        if (images[WALLNUT]==NULL) {
               printf("Error: %s\n", SDL_GetError());
        }
        SDL_SetColorKey(images[WALLNUT], SDL_TRUE, SDL_MapRGB(images[WALLNUT]->format, 255, 255, 255));

        images[SUNFLOWER] = SDL_LoadBMP("../bin/media/Sunflower.bmp");
        if (images[SUNFLOWER]==NULL) {
              printf("Error: %s\n", SDL_GetError());
        }
        SDL_SetColorKey(images[SUNFLOWER], SDL_TRUE, SDL_MapRGB(images[SUNFLOWER]->format, 255, 255, 255));


        //Apply image to screen
        if( SDL_BlitSurface( background, NULL, gScreenSurface, NULL )<0) {
                printf("Error: %s\n", SDL_GetError());
        }
        //Update Screen
        if (SDL_UpdateWindowSurface( screen )<0)printf("Error: %s\n", SDL_GetError()) ;



}

void World::destroyWorld(){

    SDL_FreeSurface( background );
    SDL_FreeSurface( images[ZOMBIE] );
    SDL_FreeSurface( images[PEASHOOTER] );
    SDL_FreeSurface( images[WALLNUT] );
    SDL_DestroyWindow( screen );
}

void World::draw(){

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(grid[i][j] != NULL){
                actorType type = grid[i][j]->getType();
                SDL_Rect temp = {(short int)(256+j*80),(short int)(80+i*100),100,62};
                if(SDL_BlitSurface(images[type],NULL,gScreenSurface,&temp)<0){
                    printf("Error: %s\n", SDL_GetError());
                }
                if(SDL_UpdateWindowSurface( screen )<0) {
                    printf("Error: %s\n", SDL_GetError());
                }
                //SDL_Delay(250);
            }
        }
    }
}

