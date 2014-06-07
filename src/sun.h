#ifndef SUN_H
#define SUN_H
#ifndef SDL_H
#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#endif
#define SUN_SIZE 62
#define PI 3.14159265
#define arc 75
#include <cmath>
class Sun
{
public:
    Sun(int inX,int inY,int inDestinationX,int inDestinationY);
    Sun();
    ~Sun();
     double timeToTravel;
     int sunSpeed;
     int timeCreated;
     int x;
     int startX;
     int rightX;
     int y;
     int startY;
     int bottomY;
     int destinationX;
     int destinationY;

     void falling();

     int getTimeLeft() { return timeLeft; }
    void setTimeLeft( int val) { timeLeft = val; }
     int getSunValue() { return sunValue; }
    void setsunValue( int val) { sunValue = val; }
    bool getCollected() { return collected; }
    void setCollected( bool val) { collected = val; }

private:

     int timeLeft;
     int sunValue;
     bool collected;
};

#endif // SUN_H
