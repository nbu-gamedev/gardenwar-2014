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
    counter_test = 0;
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
bool Actor::timeToAct(){
    return counter>=speed;
}

Zombie::Zombie(){

    type = ZOMBIE;
    act = ATTACK;
    speed = 7;
    health = 100;
    counter = 0;
    damage = 25;
    counter_test = 0;
    mover = 1;
}

Peashooter::Peashooter(){

    type = PEASHOOTER;
    act = STAY;
    speed = 4;
    health = 55;
    counter=0;
    damage = 20;
    counter_test = 0;
    mover = 1;
}

Wallnut::Wallnut(){

    type = WALLNUT;
    act = STAY;
    health = 120;
    counter = 0;
    speed = 10;
    damage = 0;
    counter_test = 0;
    mover = 1;
}
Sunflower::Sunflower(){

    type = SUNFLOWER;
    act = STAY;
    health = 30;
    counter = 0;
    speed = 12;
    damage = 0;
    counter_test = 0;
    mover = 1;
}

int Actor::return_counter()
{
    return counter_test;
}

void Actor::fill_counter(int mover)
{
    counter_test += mover;
}

int Actor::return_mover()
{
    return mover;
}

void Actor::fill_mover(int change)
{
    mover = change;
}




