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
	int counter = 0;
    bool allow = false;

    level.grid[3][2] = new Sunflower();
    level.grid[1][1] = new Peashooter();
    level.grid[2][2] = new Wallnut();
    level.grid[0][8] = new Zombie();
    level.grid[0][7] = new Zombie();
    level.grid[0][6] = new Wallnut();

	while( !World::quit ){
		while( SDL_PollEvent( &event ) != 0 ) {
		    if (event.type == SDL_MOUSEBUTTONUP){
<<<<<<< HEAD
=======
                // if player clicks on sun -> collect it
             //   for (int i=0 ; i < level.suns.size(); i++) {
              //      if ( level.suns[i]->Getx() > 0 ) {
               //         cout << "sun # " << i << " is located at x:" << level.suns[i]->Getx() << endl;
              //      }
            //    }
>>>>>>> 973b3eab182f4717c47417855245ed9548e61162
                if ( (event.button.x > gridStartX) && (event.button.x < gridEndX) &&
                     (event.button.y > gridStartY) && (event.button.y < gridEndY) ) {
                    createPeashooter(&level,event);
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
		}
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


















