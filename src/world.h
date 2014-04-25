#ifndef WORLD_H
#define WORLD_H
#include <SDL.h>
#include "actor.h"
#include "sun.h"
#include <vector>
#define N 5
#define M 9

using namespace std;

class World
{
public:
    static bool quit;
    Actor* grid[N][M];
    World();
    ~World();
    void createWorld();
    void destroyWorld();
    void draw();
    void update();
    void gameOver();
    void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
    vector<SDL_Surface*> Images[4];
    SDL_Surface* ScreenSurface;
private:
    SDL_Window* Window;
    SDL_Surface* Background;
    SDL_Surface* game_over;
};

#endif // WORLD_H
