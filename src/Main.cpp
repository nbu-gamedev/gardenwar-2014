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

    level.grid[0][2] = new Sunflower();

	while( !World::quit ){
		level.apply_surface(300,300,level.Images[0][0], level.ScreenSurface);
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
		level.draw();
		SDL_Delay(100);
	}
	level.destroyWorld();
	SDL_Quit();
	return 0;
}
