#include "world.h"
#include <iostream>
#include <ctime>
using namespace std;
bool World::quit=false;
const int gridStartX = base_x;
const int gridEndX = base_x + M*offset_x;
const int gridStartY = base_y;
const int gridEndY = base_y + N*offset_y;
void createPeashooter(World* world,SDL_Event event);

int main( int argc, char* args[] ){


    World level = World();
	level.createWorld();
	SDL_Event event;
	time_t curr=0,last=0;
    time(&curr);
	last=time(&curr);

    level.grid[3][2] = new Sunflower();
    level.grid[1][1] = new Peashooter();
    level.grid[2][2] = new Wallnut();
    level.grid[0][8] = new Zombie();
    level.grid[0][7] = new Zombie();

	while( !World::quit ){
		while( SDL_PollEvent( &event ) != 0 ){
		    if (event.type == SDL_MOUSEBUTTONUP){
                // if player clicks inside the grid
                if ( (event.button.x > gridStartX) && (event.button.x < gridEndX) &&
                     (event.button.y > gridStartY) && (event.button.y < gridEndY) ) {
                    createPeashooter(&level,event);
                }
                if( (event.type == SDL_QUIT) || (event.key.keysym.sym)== SDLK_ESCAPE){
                    World::quit = true;
                }
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

void createPeashooter(World* world,SDL_Event event){
    int row = 0;
    int column = 0;

    // Place Peashooter at clicked grid location
    column = (event.button.x - base_x)/offset_x;
    row = (event.button.y - base_y)/offset_y;
    cout << "column:" << column << " row:" << row << " address:"
    << world->grid[row][column] << endl; //6te mahna testovete kato sam naprava i Sun.

    if (world->grid[row][column] == NULL) {
        world->grid[row][column] = new Peashooter();
        cout << "Placed new peashooter" << endl; //6te mahna testovete kato sam naprava i Sun.
    }
}


















