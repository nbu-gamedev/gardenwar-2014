#ifndef ACTOR_H
#define ACTOR_H
#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

enum actorType {SUNFLOWER,PEASHOOTER,WALLNUT,ZOMBIE,ALL};
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
    virtual void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*)){};
    //virtual void upadte(int i,int j);

};

class Zombie:public Actor{
public:
    Zombie();
    void incCounter();
    bool timeToAct();
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};

class Flower:public Actor{
public:
};
class Peashooter:public Flower{
public:
    Peashooter(int x);
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};
class Wallnut:public Flower{
public:
    Wallnut(int x);
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};

class Sunflower:public Flower
{
public:
    Sunflower(int x);
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};

struct Pea{
	int x;
	int y; // = i ot grid-a
	int br; // broq4 za draw (?)
	Actor* aim;
	Pea(int psPos, int i, Actor* enemy):x(psPos+80),y(i),br(0),aim(enemy){}; //psPos -> peashooter position
	int getPlace(); //vry6ta teku6toto j ot grida
	void move();
	bool reachedAim();
	bool enemyIsDead();
};

#endif
