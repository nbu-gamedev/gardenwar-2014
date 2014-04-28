#ifndef ACTOR_H
#define ACTOR_H
#include <SDL.h>
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
public:
    virtual ~Actor(){};
    void setHP(int n);
    int getHP();
    actorType getType();
    actorAct getAct();
    void setAct(actorAct act);
    int getDamage();
    void fill_move_counter(){counter++;}
    int return_move_counter(){return counter;}
    int getCounter();
    void incCounter();
    int return_counter();
    void fill_counter(int mover);
    int return_mover();
    void fill_mover(int change);
    bool timeToAct();
    virtual void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*)){};
    //virtual void upadte(int i,int j);
    //int state(){return counter%speed;}

};

class Zombie:public Actor{
public:
    Zombie();
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};

class Flower:public Actor{
public:
};
class Peashooter:public Flower{
public:
    Peashooter();
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};
class Wallnut:public Flower{
public:
    Wallnut();
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};

class Sunflower:public Flower
{
public:
    Sunflower();
    void draw_self(int j, int i, SDL_Surface* picture, SDL_Surface* Screen, void (*apply_surface_pointer)(int, int, SDL_Surface*, SDL_Surface*));
};

#endif
