#ifndef ACTOR_H
#define ACTOR_H
#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#define ALL_SHOP_ITEMS ZOMBIE

const int base_x = 256;
const int base_y = 85;
const int offset_x = 80;
const int offset_y = 98;

enum actorType {PEASHOOTER,SUNFLOWER,WALLNUT,ZOMBIE,ALL};
enum actorAct {MOVE,ATTACK,STAY,DIE};

class Actor{
protected:
    actorType type;
    int health;
    int counter;
    int speed;
    int counter_test;
    int mover;
    actorAct act;
    int damage;
    int posX;
public:
    virtual ~Actor(){};
    void addHP(int n);
    int getHP();
    actorType getType();
    actorAct getAct();
    void setAct(actorAct act);
    int getDamage();
    int getPosX();
    void fill_move_counter(){counter++;}
    int return_move_counter(){return counter;}
    int getCounter();
    virtual void incCounter();
    int return_counter();
    void fill_counter(int mover);
    int return_mover();
    void fill_mover(int change);
    virtual bool timeToAct();
    virtual void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen){};
    //virtual void upadte(int i,int j);

};

class Zombie:public Actor{
public:
    Zombie();
    void incCounter();
    bool timeToAct();
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen);
};

class Flower:public Actor{
public:
};
class Peashooter:public Flower{
public:
    Peashooter(int x);
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen);
};
class Wallnut:public Flower{
public:
    Wallnut(int x);
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen);
};

class Sunflower:public Flower
{
public:
    Sunflower(int x);
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen);
};

struct Pea{
	int x;
	int y; // = i ot grid-a
	int br; // broq4 za draw (?)
	Actor* aim;
	Pea(int psPos, int i, Actor* enemy):x(psPos+offset_x),y(i),br(0),aim(enemy){}; //psPos -> peashooter position
	int getPlace(); //vry6ta teku6toto j ot grida
	void move(int dist);
	bool reachedAim();
	bool enemyIsDead();
};

#endif
