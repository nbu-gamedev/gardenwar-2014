#include "actor.h"


actorType Actor::getType(){
    return type;
}

int Actor::getHP(){
    return health;
}

actorAct Actor::getAct(){
    return act;
}

void Actor::setAct(actorAct act,int x){
    this->act=act;
    if (act==DIE) counter = 0;
    else counter = -1;
    counter_test = 0;
}

int Actor::getCounter(){
    return counter;
}

void Actor::incCounter(){
    counter++;
}

int Actor::getPosX(int){
    return posX;
}

int Actor::getDamage(){
    return damage;
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

bool Actor::timeToAct(){
    if(act==DIE) {return counter>=3;} //za sega 3, za da umirat po-byrzo...
    return counter%(speed+1)==0;
}

void Actor::addHP(int n){
    health = health + n;
}

Zombie::Zombie(int creationTime){

    type = ZOMBIE;
    act = MOVE;
    speed = 7;
    health = 100;
    counter = 0;
    damage = 25;
    counter_test = 0;
    mover = 1;
    posX = 915; // (endGrid - zombie) gore dolu.... !trqbva da byde promeneno
    timeMoved = creationTime;
    time_picture_changed = SDL_GetTicks();
}

void Zombie::setAct(actorAct act, int currTime){
    if (act==DIE) counter = 0;
    else if (act==MOVE){
        posX -= offset_x;// getPosX(currTime);
        counter = 0;
        timeMoved = currTime;
    }
    else counter = -1;

    counter_test = 0;
    this->act=act;
}

int Zombie::getPosX(int currTime){
    if (act==MOVE) return (posX - (currTime - timeMoved)/1000.*speed);
    return posX;
}

bool Zombie::timeToAct(){
	if(act==DIE) {return counter>=3;}
    return counter>=speed;
}


void Zombie::draw_self(int j, int i, Image Images, SDL_Surface* Screen, int time)
{
    int current_time = SDL_GetTicks();
    SDL_Rect destination;
    SDL_Rect image;
    destination.h = 0;
    destination.w = 0;
    image.h = Images.image_h;
    image.w = Images.image_w;
    image.x = 0;
    image.y = Images.image_h * counter_test;

    if(act == MOVE)
    {
        if(counter % 8 < 4)
        {
            destination.x = base_x + j*offset_x - 30 + 0.4 * counter_test;
            destination.y = base_y + i*offset_y - 50;
            SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
            SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
            if(current_time >= time_picture_changed + 1000 / Images.frames_per_second)
            {
                counter_test += 1;
                time_picture_changed = current_time;
                if(counter_test == Images.number_of_pictures[act]+1)
                {
                    counter_test -= Images.number_of_pictures[act];
                }
            }
        }
        else
        {
            destination.x = base_x + j*offset_x - 80 + 0.55 * counter_test;
            destination.y = base_y + i*offset_y - 50;
            SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
            SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
        }
        if(current_time >= time_picture_changed + 1000 / Images.frames_per_second)
        {
            counter_test += 1;
            time_picture_changed = current_time;
            if(counter_test == Images.number_of_pictures[act]+1)
            {
                counter_test -= Images.number_of_pictures[act];
            }
        }
    }
    else
    {
        destination.x = base_x + j*offset_x + 40;
        destination.y = base_y + i*offset_y - 50;
        SDL_SetColorKey(Images.animation[act], SDL_TRUE, SDL_MapRGB(Images.animation[act]->format, 0, 255, 0));
        SDL_BlitSurface(Images.animation[act], &image, Screen, &destination);
        if(current_time >= time_picture_changed + 1000 / Images.frames_per_second)
        {
            counter_test += 1;
            if(counter_test == Images.number_of_pictures[act])
            {
                counter_test -= Images.number_of_pictures[act];
            }
            time_picture_changed = current_time;
        }
    }
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
    time_picture_changed = SDL_GetTicks();
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
    time_picture_changed = SDL_GetTicks();
}

void Wallnut::draw_self(int j, int i, Image Images, SDL_Surface* Screen, int time)
{
    int current_time = SDL_GetTicks();
    if(current_time >= time_picture_changed + 1000 / Images.frames_per_second)
    {
        counter_test += mover;
        time_picture_changed = current_time;
    }
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
    time_picture_changed = SDL_GetTicks();
}

void Sunflower::draw_self(int j, int i, Image Images, SDL_Surface* Screen, int time)
{
    int current_time = SDL_GetTicks();
    if(current_time >= time_picture_changed + 1000 / Images.frames_per_second)
    {
        counter_test += mover;
        time_picture_changed = current_time;
    }
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

void Peashooter::draw_self(int j, int i, Image Images, SDL_Surface* Screen, int time)
{
    int current_time = SDL_GetTicks();
    if(current_time >= time_picture_changed + 1000 / Images.frames_per_second)
    {
        counter_test += mover;
        time_picture_changed = current_time;
    }
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
    if(counter_test >= Images.number_of_pictures[act])
        mover = -1;
    if(counter_test <= 0)
        mover = 1;
}

// Pea:


int Pea::getCurrPeaPos(int currTime){
 return (startPos+speed*(currTime-creationTime)/1000.);
}

int Pea::getPlace(int currTime){ // current position j on grid
	return (getCurrPeaPos(currTime)-base_x)/offset_x;
}
bool Pea::reachedAim(int currTime){
	if(aim!=NULL){
		return (getCurrPeaPos(currTime) >= aim->getPosX(currTime)); //sledva da byde doobraboteno....
	}
	return false;
}
bool Pea::enemyIsDead(){
  return  ( aim!=NULL && aim->getAct()==DIE ); // 2 = zombieDieSpeed - 1...
}

