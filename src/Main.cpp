#include "world.h"
#include <iostream>
#include <ctime>
using namespace std;
bool World::quit=false;

int main( int argc, char* args[] ){
 srand (time(NULL));
    World level = World();
	level.createWorld();
	SDL_Event event;
	int counter = 0;
    bool allow = false;
    bool clickedOnSun = false;
    srand (time(NULL));
    int timeToSun = level.sunSpawnTime;

    level.grid[3][2] = new Sunflower();
    level.grid[1][1] = new Peashooter();
    level.grid[2][2] = new Wallnut();
    level.grid[0][3] = new Wallnut();
    level.grid[0][4] = new Wallnut();
    level.grid[0][5] = new Wallnut();
    level.grid[0][8] = new Zombie();

	while( !World::quit ){
		while( SDL_PollEvent( &event ) != 0 ) {
		    if (event.type == SDL_MOUSEBUTTONUP){
             // if player clicks on sun -> collect it
                clickedOnSun = false;
                for (int i=0 ; i < level.suns.size(); i++) {
                    if ( (event.button.x > level.suns[i]->getX()) && (event.button.x < level.suns[i]->getRightX() ) &&
                         (event.button.y > level.suns[i]->getY()) && (event.button.y < level.suns[i]->getBottomY()) ) {
                        level.setSunCurrency(level.suns[i]->getSunValue());
                        cout << "$$$: " << level.getSunCurrency() << endl;
                        delete level.suns[i];
                        level.suns.erase(level.suns.begin() + i);
                        clickedOnSun = true;
                        break;
                    }
                }
                if ( ( !clickedOnSun ) &&
                     (event.button.x > gridStartX) && (event.button.x < gridEndX) &&
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


















