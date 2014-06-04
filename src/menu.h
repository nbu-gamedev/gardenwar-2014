#ifndef MENU_H
#define MENU_H
#include "world.h"
#include <ctime>

class Menu
{
public:
    Menu();
    void handle_menu();
    void start_game();
    void show_instructions();
private:
    SDL_Window* Window;
    SDL_Surface* ScreenSurface;
    SDL_Surface* title_screen;
    SDL_Surface* instructions;
friend void menu_factory(Menu &Game);
};

#endif
