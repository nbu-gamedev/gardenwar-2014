#ifndef ACTOR_H
#define ACTOR_H

enum actorType {ZOMBIE,PEASHOOTER,WALLNUT,SUNFLOWER,ALL};
enum actorAct {MOVE,ATTACK,STAY,DIE};

class Actor{
protected:

    actorType type;
    int health;
    int counter;
    int speed;
    actorAct act;
    int damage;
public:

    void setHP(int n);
    int getHP();
    actorType getType();
    actorAct getAct();
    void setAct(actorAct act);
    int getDamage();
    int getCounter();
    void incCounter();
    //virtual void upadte(int i,int j);
    //int state(){return counter%speed;}

};

class Zombie:public Actor{
public:
    Zombie();
};

class Flower:public Actor{
public:
};
class Peashooter:public Flower{
public:
    Peashooter();
};
class Wallnut:public Flower{
public:
    Wallnut();
};

class Sunflower:public Flower
{
public:
    Sunflower();
};

#endif
