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
    virtual void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen){};
    //virtual void upadte(int i,int j);
};

class Zombie:public Actor{
public:
    Zombie(int);
    bool timeToAct();
    int getPosX(int);
    void setAct(actorAct act, int currTime = 0);
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen);
private:
    int timeMoved;
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
	int pos;
	int x; // = j ot grid-a
	int y; // = i ot grid-a
	Actor* creator;
	Actor* aim;
	int prTime;
	Pea(int psPos, int i, Actor* enemy, Actor* crtr, int time ):pos(psPos+offset_x),x(psPos),y(i),aim(enemy),creator(crtr),prTime(time){}; //psPos -> peashooter position
	int getPlace(); //vry6ta teku6toto j ot grida
	void move(int, int);
	bool reachedAim(int);
	bool enemyIsDead();
	int getCurrPeaPos(int, int);
};

#endif
