#include <SDL.h>
#include "Actor.h"
#ifndef WORLD_H
#define WORLD_H
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 600
#define N 5
#define M 9

class World
{
    public:
        Actor* grid[N][M]; // temp posle 6te e privet ( v momenta setvame zombita v main)

        World();
        ~World();
        void createWorld();
        void destroyWorld();
        void draw();


            /*void update(){
    	for(int i=0; i<N; i++){
    		for(int j=0; j<M; j++){
    			if(grid[i][j] != NULL){
    				grid[i][j]->action(i, j, grid[i][j--]);
    			}
    		}
    	}

    }*/


    protected:

    private:
        SDL_Surface* gScreenSurface;
        SDL_Surface* images[ALL];
        SDL_Surface* background;
        SDL_Window* screen;
};

#endif // WORLD_H
