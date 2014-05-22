#ifndef WORLD_H
#define WORLD_H
#include "actor.h"
#include "sun.h"
#include "images.h"
#include "sound.h"
#include <vector>
#include <list>
#include <cstdlib>
#define N 5
#define M 9

const int gridStartX = base_x;
const int gridEndX = base_x + M*offset_x;
const int gridStartY = base_y;
const int gridEndY = base_y + N*offset_y;
const int gridSizeX = gridEndX - gridStartX;
const int gridSizeY = gridEndY - gridStartY;


//shopitems
struct ItemsInShop{
    int x,y,sideX,bottomY;
    int cost;
    bool clicked;
    bool mouseOver();
};

class World
{
public:
    static bool quit;

    list<Actor*> grid[N][M];

    World();
    ~World();
    void readData();
    void createWorld();
    void destroyWorld();

    void draw(int);
    void update(int);
    void peaShooting(int);

    void gameOver(bool);
    // Shop
    ItemsInShop ShopItem[ALL_SHOP_ITEMS];
    bool canAfford(ItemsInShop item);
    bool clickedOnShop;
    // Sun
    void createSun();
    void createDefender(SDL_Event &event);
    void createPeashooter(SDL_Event &event);
    void createSunflower(SDL_Event &event);
    void createWallnut(SDL_Event &event);
    vector<Sun*> suns;
    int sunSpawnTime;
    static void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
    void setSunCurrency(int val){sunCurrency+=val;}
    int getSunCurrency() {return sunCurrency;}
private:
	SDL_Surface* peaImagePH;
	SDL_Surface* peaShadowImagePH;
    SDL_Surface* sunImagePH;
    SDL_Surface* numbersSpite;
    SDL_Surface* shopSprite;
    SDL_Surface* ScreenSurface;
    SDL_Window* Window;
    SDL_Surface* Background;
    SDL_Surface* gameOverScreen;
    SDL_Surface* winnerScreen;
    Image Creature_images[4];
    Sound_master Sounds;
    int sunCurrency;
    list<Pea*> peas;
    int peaSpeed;
    vector<int>* zombieWaves;
    int zombieWavesLength;
};


#endif // WORLD_H

