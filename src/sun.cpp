#include "sun.h"
#include <iostream>
using namespace std;
Sun::Sun(int inX,int inY)
{
    x = inX;
    y = inY;
    timeLeft = 15;
    sunValue = 20;
    collected = false;
    cout << endl << x << endl;
    cout << endl << y << endl;
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
