#include "world.h"

bool World::quit=false;

int main( int argc, char* args[] )
{
    srand (time(NULL));
    Menu Game;
    menu_factory(Game);
    Game.handle_menu();

	return 0;
}
