#ifndef WORLD_H
#define WORLD_H
#include "actor.h"
#include "sun.h"
#include <vector>
#include <list>
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
//shopitems
struct ItemsInShop{
    int x,y,height,width;
    int cost;
    bool mouseOver,clicked,canAfford;
};





using namespace std;

class World
{
public:
    static bool quit;
    list<Actor*> grid[N][M];
    World();
    ~World();
    void createWorld();
    void destroyWorld();
    void draw();
    void update(int);
    void gameOver();
    // Shop
    ItemsInShop ShopItem[ALL_SHOP_ITEMS];
    // Sun
    void createSun();
    void createPeashooter(SDL_Event event);
    vector<Sun*> suns;
    int sunSpawnTime;
    static void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
    void setSunCurrency(int val){sunCurrency+=val;}
    int getSunCurrency() {return sunCurrency;}
private:
	SDL_Surface* peaImagePH;
    SDL_Surface* sunImagePH;
    SDL_Surface* numbersSpite;
    SDL_Surface* shopSprite;
    vector<SDL_Surface*> Images[5];
    SDL_Surface* ScreenSurface;
    SDL_Window* Window;
    SDL_Surface* Background;
    SDL_Surface* game_over;
    void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*);
    int sunCurrency;
    list<Pea*> peas;
    vector<int> zombieWaves[300];
    void readData();
};

#endif // WORLD_H
