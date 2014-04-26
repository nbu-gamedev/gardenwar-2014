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
    int row = 0;
    int column = 0;
    int gridStartX = base_x;
    int gridEndX = base_x + M*offset_x;
    int gridStartY = base_y;
    int gridEndY = base_y + N*offset_y;

    level.grid[3][2] = new Sunflower();
    level.grid[1][1] = new Peashooter();

	while( !World::quit ){
		while( SDL_PollEvent( &event ) != 0 ){
			if( (event.type == SDL_QUIT) || (event.key.keysym.sym)== SDLK_ESCAPE){
				World::quit = true;
			}
			// if player clicks inside the grid
            else if ( (event.type == SDL_MOUSEBUTTONUP) && (event.button.x > gridStartX) &&
                 (event.button.x < gridEndX) && (event.button.y >gridStartY) && (event.button.y < gridEndY) ) {
                // Place Peashooter at clicked grid location
                column = (event.button.x - base_x)/offset_x;
                row = (event.button.y - base_y)/offset_y;
                cout << "column:" << column << " row:" << row << " address:" << level.grid[row][column] << endl; //6te mahna testovete kato sam naprava i Sun.
                if (level.grid[row][column] == NULL) {
                    level.grid[row][column] = new Peashooter();
                    cout << "Placed new peashooter" << endl; //6te mahna testovete kato sam naprava i Sun.
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
