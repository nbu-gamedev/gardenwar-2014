#include "sun.h"
#include <iostream>

using namespace std;
Sun::Sun(int inX,int inY,int inDestinationX,int inDestinationY)
{
    timeCreated = SDL_GetTicks();
    x = inX;
    y = inY;
    destinationX = inDestinationX;
    destinationY = inDestinationY;
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
