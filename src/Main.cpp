#include "world.h"
#include <iostream>
#include <ctime>
using namespace std;
bool World::quit=false;


int main( int argc, char* args[] ){

    World level = World();
	level.createWorld();
	SDL_Event event;
	time_t curr=0,last=0;
    time(&curr);
	last=time(&curr);
	int counter = 0;
    int turnsToSun = 15;
    bool allow;

    level.grid[3][2] = new Sunflower();
    level.grid[1][1] = new Peashooter();
    level.grid[2][2] = new Wallnut();
    level.grid[0][8] = new Zombie();

	while( !World::quit ){
		while( SDL_PollEvent( &event ) != 0 ) {
		    if (event.type == SDL_MOUSEBUTTONUP){
                // if player clicks inside the grid
                if ( (event.button.x > gridStartX) && (event.button.x < gridEndX) &&
                     (event.button.y > gridStartY) && (event.button.y < gridEndY) ) {
                    level.createPeashooter(event);
                }
            }
            if( (event.type == SDL_QUIT) || (event.key.keysym.sym)== SDLK_ESCAPE){
                World::quit = true;
                }
            }
		time(&curr);
        if(SDL_GetTicks() % 100  == 0)
        {
            level.draw();
            counter++;
            if (counter % 10 == 0)
                allow = true;
        }
        if(allow)
        {
			level.update();
			allow = false;
			turnsToSun--;
            if (turnsToSun <=0){
                level.createSun();
                turnsToSun = level.sunSpawnTime;
           }
        }
	}
	level.destroyWorld();
	SDL_Quit();
	return 0;
}



















