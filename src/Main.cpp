#include "world.h"

#include <ctime>

bool World::quit=false;
int main( int argc, char* args[] ){


    World level = World();
	level.createWorld();
	SDL_Event event;
	time_t curr=0,last=0;
    time(&curr);
	last=time(&curr);
    level.grid[0][1]= new Wallnut();
	level.grid[0][0]= new Peashooter();
	level.grid[1][5]= new Zombie();
	level.grid[3][6]= new Zombie();
	level.grid[1][1]= new Sunflower();
	level.grid[2][5]= new Zombie();
	level.grid[3][1]= new Peashooter();
	level.grid[2][1]= new Wallnut();
	level.grid[1][2]= new Peashooter();
	level.grid[1][7]= new Peashooter();

	while( !World::quit ){
		level.draw();
		while( SDL_PollEvent( &event ) != 0 ){
			if( (event.type == SDL_QUIT) || (event.key.keysym.sym)== SDLK_ESCAPE){
				World::quit = true;
			}
		}
		time(&curr);
		if(curr-last>=1){
			last=time(&curr);
			level.update();
		}
	}
	level.destroyWorld();
	SDL_Quit();
	return 0;
}
