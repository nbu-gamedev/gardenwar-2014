#include "sun.h"

Sun::Sun(int inX,int inY,int inDestinationX,int inDestinationY)
{
    timeCreated = SDL_GetTicks();
    sunSpeed = 10;
    x = inX;
    y = inY;
    startX = x;
    startY = y;
    destinationX = inDestinationX;
    destinationY = inDestinationY;
    timeToTravel = (sqrt(startX*startX+startY*startY)/sunSpeed)*1000;

    rightX = x+SUN_SIZE;
    bottomY = y+SUN_SIZE;
    timeLeft = 15;
    sunValue = 25;
    collected = false;
}
Sun::Sun()
{
    x = 0;
    y = 0;
    timeLeft = 15;
    sunValue = 20;
    collected = false;
}
Sun::~Sun()
{
    //dtor
}

void Sun::falling(){

}
