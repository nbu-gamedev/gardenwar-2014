#include "actor.h"

/*Actor::Actor()
{
    //ctor
}

Actor::~Actor()
{
    //dtor
}*/


actorType Actor::getType(){

    return type;
}

void Actor::setHP(int n){
    	health = health + n;
    }

Zombie::Zombie(){

    type = ZOMBIE;
    speed = 4;
    health = 100;
    counter=0;
}
Peashooter::Peashooter(){

    type = PEASHOOTER;
    speed = 4;
    health = 50;
    counter=0;
}
Wallnut::Wallnut()
{
    type = WALLNUT;
    health = 120;
    counter = 0;
    speed = 10;
}
Sunflower::Sunflower()
{
    health = 30;
    type = SUNFLOWER;
    counter = 0;
    speed = 12;
}




