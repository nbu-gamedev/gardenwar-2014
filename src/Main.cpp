#include "world.h"
#include <iostream>
#include <ctime>
using namespace std;
bool World::quit=false;

int main( int argc, char* args[] ){

    World level = World();
	level.createWorld();
	SDL_Event event;
	int counter = 0;
    bool allow = false;
    int timeToSun = level.sunSpawnTime;

    level.grid[3][2] = new Sunflower();
    level.grid[1][1] = new Peashooter();
    level.grid[2][2] = new Wallnut();
    level.grid[0][8] = new Zombie();
    level.grid[0][7] = new Zombie();
    level.grid[0][6] = new Wallnut();

	while( !World::quit ){
		while( SDL_PollEvent( &event ) != 0 ) {
		    if (event.type == SDL_MOUSEBUTTONUP){
             // if player clicks on sun -> collect it
                for (int i=0 ; i < level.suns.size(); i++) {
                    if ( level.suns[i]->Getx() > 0 ) {
                        cout << "sun # " << i << " is located at x:" << level.suns[i]->Getx() << endl;
                    }
                }
                if ( (event.button.x > gridStartX) && (event.button.x < gridEndX) &&
                     (event.button.y > gridStartY) && (event.button.y < gridEndY) ) {
                    level.createPeashooter(event);
                }
            }
            if( (event.type == SDL_QUIT) || (event.key.keysym.sym)== SDLK_ESCAPE){
                World::quit = true;
            }
        }
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
			cout<<" E "<<endl;
			timeToSun--;
			if (timeToSun<=0){
                level.createSun();
                timeToSun = level.sunSpawnTime;
			}
		}
	}
	level.destroyWorld();
	SDL_Quit();
	return 0;
}


















