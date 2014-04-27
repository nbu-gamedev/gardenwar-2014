#ifndef WORLD_H
#define WORLD_H
#include <SDL.h>
#include "actor.h"
#include "sun.h"
#include <vector>
#include <cstdlib>
#define N 5
#define M 9
const int base_x = 256;
const int base_y = 85;
const int offset_x = 80;
const int offset_y = 98;
const int gridStartX = base_x;
const int gridEndX = base_x + M*offset_x;
const int gridStartY = base_y;
const int gridEndY = base_y + N*offset_y;
const int gridSizeX = gridEndX - gridStartX;
const int gridSizeY = gridEndY - gridStartY;


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
    //sun
    void createSun();
    void createPeashooter(SDL_Event event);
    vector<Sun*> suns;
    int sunSpawnTime;
    void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
private:
    vector<SDL_Surface*> Images[5];
    SDL_Surface* ScreenSurface;
    SDL_Window* Window;
    SDL_Surface* Background;
    SDL_Surface* game_over;
};

#endif // WORLD_H
