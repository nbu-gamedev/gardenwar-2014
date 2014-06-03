#include "world.h"
#include <iostream>
#include <ctime>

bool World::quit=false;

int main( int argc, char* args[] ){
    World level = World();
	level.createWorld();
	SDL_Event event;
    bool clickedOnSun = false;
    srand (time(NULL));
    int timeToSun = level.sunSpawnTime;
    unsigned int lastTime = 0, lastTimeDraw = 0, currentTime, lastTimeMoved = 0;
    currentTime = 0;
    level.grid[3][2].push_back(new Sunflower(2));

	while( !World::quit ){
        currentTime = SDL_GetTicks();
		while( SDL_PollEvent( &event ) != 0 ) {
            if( event.type == SDL_QUIT){//} || (event.key.keysym.sym)== SDLK_ESCAPE){
                World::quit = true;
            }
		    if (event.type == SDL_MOUSEBUTTONUP){
                // if player clicks on sun -> collect it
                clickedOnSun = false;
                for (unsigned int i=0 ; i < level.suns.size(); i++) {
                    if ( (event.button.x > level.suns[i]->x) && (event.button.x < level.suns[i]->rightX ) &&
                         (event.button.y > level.suns[i]->y) && (event.button.y < level.suns[i]->bottomY ) ) {
                        // level.setSunCurrency(level.suns[i]->getSunValue());
                        // cout << "$$$: " << level.getSunCurrency() << endl;
                        level.collectedSuns.push_back(new Sun(level.suns[i]->x,level.suns[i]->y,5,5));
                        delete level.suns[i];
                        level.suns.erase(level.suns.begin() + i);
                        clickedOnSun = true;
                        break;
                    }
                }
                 for (unsigned int i=0 ; i < level.naturalSuns.size(); i++) {
                    if ( (event.button.x > level.naturalSuns[i]->x) && (event.button.x < level.naturalSuns[i]->rightX ) &&
                         (event.button.y > level.naturalSuns[i]->y) && (event.button.y < level.naturalSuns[i]->bottomY ) ) {
                        //level.setSunCurrency(level.naturalSuns[i]->getSunValue());
                        // cout << "$$$: " << level.getSunCurrency() << endl;
                        level.collectedSuns.push_back(new Sun(level.naturalSuns[i]->x,level.naturalSuns[i]->y,5,5));
                        delete level.naturalSuns[i];
                        level.naturalSuns.erase(level.naturalSuns.begin() + i);
                        clickedOnSun = true;
                        break;
                    }
                }
                if ( ( !clickedOnSun ) && (level.clickedOnShop) &&
                     (event.button.x > gridStartX) && (event.button.x < gridEndX) &&
                     (event.button.y > gridStartY) && (event.button.y < gridEndY) ) {
                    level.createDefender(event);
                    break;
                }
                for (int i = 0; i < ALL_SHOP_ITEMS ; i++){
                    level.ShopItem[i].clicked = (level.ShopItem[i].mouseOver() && level.canAfford(level.ShopItem[i]) );
                    level.clickedOnShop = true;
                }

            }

        }

        if (currentTime >= lastTimeMoved +30) {
            for (unsigned int i=0 ; i < level.suns.size(); i++) {
                if (level.suns[i]->x <= level.suns[i]->destinationX ) {
                    level.suns[i]->x += 3;
                    level.suns[i]->rightX += 3;
                }
            }
            for (unsigned int i=0 ; i < level.naturalSuns.size(); i++) {
                if ( level.naturalSuns[i]->y <= level.naturalSuns[i]->destinationY )
                    level.naturalSuns[i]->y += 3;
                    level.naturalSuns[i]->bottomY += 3;

            }
            for (unsigned int i=0 ; i < level.collectedSuns.size(); i++) {

                if (level.collectedSuns[i]->y >= level.collectedSuns[i]->destinationY ) {
                    level.collectedSuns[i]->y -= 3;
                }
                if (level.collectedSuns[i]->x >= level.collectedSuns[i]->destinationX ) {
                    level.collectedSuns[i]->x -= 3;
                }
                if (level.collectedSuns[i]->x <= level.collectedSuns[i]->destinationX &&
                    level.collectedSuns[i]->y <= level.collectedSuns[i]->destinationY ) {

                    level.setSunCurrency(level.collectedSuns[i]->getSunValue());
                    delete level.collectedSuns[i];
                    level.collectedSuns.erase(level.collectedSuns.begin() + i);
                }
            }
            lastTimeMoved = currentTime;
        }

        if (currentTime >= lastTimeDraw + 100)
        {
            level.peaShooting(currentTime);
            lastTimeDraw = currentTime;
            level.draw(currentTime);
        }
        if (currentTime >= lastTime + 1000)
        {
            lastTime = currentTime;
			level.update(currentTime);
			timeToSun--;
			if (timeToSun<=0){
                level.createNaturalSun();
                timeToSun = level.sunSpawnTime;
			}
		}
	}

	level.destroyWorld();
	SDL_Quit();
	return 0;
}


















