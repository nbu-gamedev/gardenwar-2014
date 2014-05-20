#include "actor.h"

actorType Actor::getType(){
    return type;
}

void Actor::addHP(int n){
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
    if ((act==DIE) || (act==MOVE)) counter = 0;
    else counter = -1;
    counter_test = 0;
}

int Actor::getCounter(){
    return counter;
}

void Actor::incCounter(){
    counter++;
}

int Actor::getPosX(){
    return posX;
}

int Actor::getDamage(){
    return damage;
}
bool Actor::timeToAct(){
    if(act==DIE) {return counter>=3;} //za sega 3, za da umirat po-byrzo...
    return counter%(speed+1)==0;
}

void Zombie::incCounter(){
    counter++;
    // za promqna na koordinati - primerno:
    if(act == MOVE) posX-=offset_x/speed;
}

bool Zombie::timeToAct(){
	if(act==DIE) {return counter>=3;}
    return counter>=speed;
}

Zombie::Zombie(){

    type = ZOMBIE;
    act = MOVE;
    speed = 7;
    health = 100;
    counter = 0;
    damage = 25;
    counter_test = 0;
    mover = 1;
    posX = 915; // (endGrid - zombie) gore dolu.... !trqbva da byde promeneno
}

Peashooter::Peashooter(int x){

    type = PEASHOOTER;
    act = ATTACK;
    speed = 1;
    health = 55;
    counter=0;
    damage = 20;
    counter_test = 0;
    mover = 1;
    posX = base_x + x*offset_x;
}

Wallnut::Wallnut(int x){

    type = WALLNUT;
    act = STAY;
    health = 120;
    counter = 0;
    speed = 10;
    damage = 0;
    counter_test = 0;
    mover = 1;
    posX = base_x + x*offset_x;
}
Sunflower::Sunflower(int x){

    type = SUNFLOWER;
    act = STAY;
    health = 30;
    counter = 0;
    speed = 12;
    damage = 0;
    counter_test = 0;
    mover = 1;
    posX = base_x + x*offset_x;
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

void Sunflower::draw_self(int j, int i, Image Images, SDL_Surface* Screen)
{
    counter_test += mover;
    SDL_Rect destination;
    SDL_Rect image;
    destination.x = base_x + j*offset_x;
    destination.y = base_y + i*offset_y;
    destination.h = 0;
    destination.w = 0;
    image.h = Images.image_h;
    image.w = Images.image_w;
    image.x = 0;
    image.y = Images.image_h * counter_test;
    SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
    SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
    if(counter_test == Images.number_of_pictures[act])
        mover = -1;
    if(counter_test == 0)
        mover = 1;
}

void Wallnut::draw_self(int j, int i, Image Images, SDL_Surface* Screen)
{
    counter_test += mover;
    SDL_Rect destination;
    SDL_Rect image;
    destination.x = base_x + j*offset_x;
    destination.y = base_y + i*offset_y;
    destination.h = 0;
    destination.w = 0;
    image.h = Images.image_h;
    image.w = Images.image_w;
    image.x = 0;
    image.y = Images.image_h * counter_test;
    SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
    SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
    if(counter_test == Images.number_of_pictures[act])
        mover = -1;
    if(counter_test == 0)
        mover = 1;
}

void Peashooter::draw_self(int j, int i, Image Images, SDL_Surface* Screen)
{
    counter_test += mover;
    SDL_Rect destination;
    SDL_Rect image;
    destination.x = base_x + j*offset_x;
    destination.y = base_y + i*offset_y;
    destination.h = 0;
    destination.w = 0;
    image.h = Images.image_h;
    image.w = Images.image_w;
    image.x = 0;
    image.y = Images.image_h * counter_test;
    SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
    SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
    if(counter_test == Images.number_of_pictures[act])
        mover = -1;
    if(counter_test == 0)
        mover = 1;
}

void Zombie::draw_self(int j, int i, Image Images, SDL_Surface* Screen)
{
    if(act == MOVE)
    {
        if(counter % 8 < 4)
        {
            SDL_Rect destination;
            SDL_Rect image;
            destination.x = base_x + j*offset_x - 30 + 0.4 * counter_test;
            destination.y = base_y + i*offset_y - 50;
            destination.h = 0;
            destination.w = 0;
            image.h = Images.image_h;
            image.w = Images.image_w;
            image.x = 0;
            image.y = Images.image_h * counter_test;
            SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
            SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
            counter_test += 1;
            if(counter_test == Images.number_of_pictures[act])
                counter_test += -Images.number_of_pictures[act];
        }
        else
        {
            SDL_Rect destination;
            SDL_Rect image;
            destination.x = base_x + j*offset_x - 80 + 0.55 * counter_test;
            destination.y = base_y + i*offset_y - 50;
            destination.h = 0;
            destination.w = 0;
            image.h = Images.image_h;
            image.w = Images.image_w;
            image.x = 0;
            image.y = Images.image_h * counter_test;
            SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
            SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
            counter_test += 1;
            if(counter_test == Images.number_of_pictures[act])
                counter_test += -Images.number_of_pictures[act];
        }
    }
    else
    {
        SDL_Rect destination;
        SDL_Rect image;
        destination.x = base_x + j*offset_x + 40;
        destination.y = base_y + i*offset_y - 50;
        destination.h = 0;
        destination.w = 0;
        image.h = Images.image_h;
        image.w = Images.image_w;
        image.x = 0;
        image.y = Images.image_h * counter_test;
        SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
        SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
        counter_test += 1;
        if(counter_test == Images.number_of_pictures[act])
            counter_test += -Images.number_of_pictures[act];
    }
}

void Pea::move(int dist){
	pos=pos+dist;
	br=0; // broq4 za draw (?)
}

int Pea::getPlace(){ // current position j on grid
	return (pos-base_x)/offset_x;
}
bool Pea::reachedAim(){
	if(aim!=NULL){
		return (pos >= aim->getPosX()); //sledva da byde doobraboteno....
	}
	return false;
}
bool Pea::enemyIsDead(){
  return  (aim!=NULL && aim->getAct()==DIE && aim->getCounter()==2); // 2 = zombieDieSpeed - 1...
}


