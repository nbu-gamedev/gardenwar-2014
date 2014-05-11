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
    bool clickedOnSun = false;
    srand (time(NULL));
    int timeToSun = level.sunSpawnTime;
    unsigned int lastTime = 0, lastTimeDraw = 0, currentTime;
    currentTime = 0;

    level.grid[3][2].push_back(new Sunflower(2));
    level.grid[0][7].push_front(new Wallnut(7));

	while( !World::quit ){

        currentTime = SDL_GetTicks();
		while( SDL_PollEvent( &event ) != 0 ) {
		    if (event.type == SDL_MOUSEBUTTONUP){
             // if player clicks on sun -> collect it
                clickedOnSun = false;
                for (unsigned int i=0 ; i < level.suns.size(); i++) {
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
        if (currentTime >= lastTimeDraw + 100)
        {
            lastTimeDraw = currentTime;
            level.draw();
            counter++;
        }
        if (currentTime >= lastTime + 1000)
        {
            lastTime = currentTime;
			level.update(currentTime);
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


















