#ifndef ACTOR_H
#define ACTOR_H

enum actorType {ZOMBIE,PEASHOOTER,WALLNUT,SUNFLOWER,ALL};

class Actor{
protected:

    actorType type;
    int health;
    int counter;
    int speed;
public:

    void setHP(int n);
    actorType getType();
    //int state(){return counter%speed;}

};

class Zombie:public Actor{
public:
    Zombie();
};

class Flower:public Actor{
public:
    //void action();
};
class Peashooter:public Flower{
public:
    Peashooter();
    //void action(){}
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
