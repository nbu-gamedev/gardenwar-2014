#include "World.h"
#include <thread>
// screen dimension constants


int main( int argc, char* args[] ){


    World level = World();
	level.createWorld();
	SDL_Event event;
    bool quit = false;

	level.grid[0][0]= new Peashooter();
	level.grid[1][5]= new Zombie();
	level.grid[3][6]= new Zombie();
	level.grid[1][1]= new Sunflower();
	level.grid[2][5]= new Zombie();
	level.grid[3][1]= new Peashooter();
	level.grid[2][1]= new Wallnut();
	level.grid[1][2]= new Peashooter();
    level.grid[1][7]= new Peashooter();

    while( !quit ){
        //Handle events on queue

        while( SDL_PollEvent( &event ) != 0 ){
            if( (event.type == SDL_QUIT) ||  (event.key.keysym.sym)== SDLK_ESCAPE){
                        quit = true;
            }
        }
         level.draw();
        SDL_Delay(1000);
    }





        //Apply the image

        //Update the surface


	//Pause
//	SDL_Delay( 20000 );
	level.destroyWorld();
	SDL_Quit();
    return 0;
}


















