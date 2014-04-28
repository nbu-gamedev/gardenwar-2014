#ifndef SUN_H
#define SUN_H

#define SUN_SIZE 62;

class Sun
{
    public:
        Sun(int inX,int inY);
        Sun();
        ~Sun();
         int getX() { return x; }
        void setX( int val) { x = val; }
         int getRightX() { return rightX; }

         int getY() { return y; }
        void setY( int val) { y = val; }
         int getBottomY() { return bottomY; }

         int getTimeLeft() { return timeLeft; }
        void setTimeLeft( int val) { timeLeft = val; }
         int getSunValue() { return sunValue; }
        void setsunValue( int val) { sunValue = val; }
        bool getCollected() { return collected; }
        void setCollected( bool val) { collected = val; }

    protected:
    private:
         int x;
         int rightX;
         int y;
         int bottomY;
         int timeLeft;
         int sunValue;
         bool collected;
};

#endif // SUN_H
