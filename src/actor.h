#ifndef ACTOR_H
#define ACTOR_H
#ifndef SDL_H
#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#endif
#define ALL_SHOP_ITEMS ZOMBIE
#include "images.h"

const int base_x = 256;
const int base_y = 85;
const int offset_x = 80;
const int offset_y = 98;

enum actorType {PEASHOOTER,SUNFLOWER,WALLNUT,ZOMBIE,ALL};
enum actorAct {MOVE,ATTACK,STAY,DIE};

class Actor{

protected:
    int counter;
    int speed;
    int health;
    int damage;
    actorType type;
    actorAct act;

    int posX;

    int counter_test;
    int mover;

public:
    virtual ~Actor(){};

    int getHP();
    actorType getType();
    actorAct getAct();
    virtual void setAct(actorAct act, int x = 0);
    int getDamage();
    virtual int getPosX(int x = 0);

    void fill_move_counter(){counter++;}
    int return_move_counter(){return counter;}
    int getCounter();
    void incCounter();
    int return_counter();
    void fill_counter(int mover);
    int return_mover();
    void fill_mover(int change);

    virtual bool timeToAct();
    void addHP(int n);

    virtual void draw_self(int j, int i, Image Images, SDL_Surface* Screen){};
    Image Self_Images;
};

class Zombie:public Actor{

public:
    Zombie(int);

    void setAct(actorAct act, int currTime = 0);
    int getPosX(int);
    bool timeToAct();

    void draw_self(int j, int i, Image Images, SDL_Surface* Screen);

private:
    int timeMoved;
};

class Flower:public Actor{};

class Peashooter:public Flower{

public:
    Peashooter(int x);

    void draw_self(int j, int i, Image Images, SDL_Surface* Screen);
};

class Wallnut:public Flower{

public:
    Wallnut(int x);

    void draw_self(int j, int i, Image Images, SDL_Surface* Screen);
};

class Sunflower:public Flower
{
public:
    Sunflower(int x);

    void draw_self(int j, int i, Image Images, SDL_Surface* Screen);
};

// Pea:

struct Pea{

	int speed ;
	int creationTime;

	int startPos;
	int y; // = i ot grid-a

	Actor* creator;
	Actor* aim;


	Pea(const int &spd, int psPos, int i, Actor* enemy, Actor* crtr, int time ):speed(spd),startPos(psPos+offset_x),y(i),aim(enemy),creator(crtr),creationTime(time){}; //psPos -> peashooter position

	int getPlace(int); //vry6ta teku6toto j ot grida
	int getCurrPeaPos(int);

	bool reachedAim(int);
	bool enemyIsDead();
};

#endif
