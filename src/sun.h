#ifndef SUN_H
#define SUN_H
#include "SDL.h"
#define SUN_SIZE 62

class Sun
{
public:
    Sun(int inX,int inY,int inDestinationX,int inDestinationY);
    Sun();
    ~Sun();
     int timeCreated;
     int x;
     int rightX;
     int y;
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
