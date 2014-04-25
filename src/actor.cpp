#include "actor.h"

actorType Actor::getType(){
    return type;
}

void Actor::setHP(int n){
    health = health + n;
}

int Actor::getHP(){
    return health;
}

actorAct Actor::getAct(){
    return act;
}
void Actor::setAct(actorAct act){
    this->act=act;
    counter = 0;
}

int Actor::getCounter(){
    return counter;
}

void Actor::incCounter(){
    counter++;
}

int Actor::getDamage(){
    return damage;
}

Zombie::Zombie(){

    type = ZOMBIE;
    act = STAY;
    speed = 4;
    health = 100;
    counter = 0;
    damage = 25;
}

Peashooter::Peashooter(){

    type = PEASHOOTER;
    act = STAY;
    speed = 4;
    health = 55;
    counter=0;
    damage = 20;
}

Wallnut::Wallnut(){

    type = WALLNUT;
    act = STAY;
    health = 120;
    counter = 0;
    speed = 10;
    damage = 0;
}
Sunflower::Sunflower(){

    type = SUNFLOWER;
    act = STAY;
    health = 30;
    counter = 0;
    speed = 12;
    damage = 0;
}




