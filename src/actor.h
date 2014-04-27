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
    int counter_test;
    int mover;
    actorAct act;
    int damage;
public:
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
