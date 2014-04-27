#ifndef SUN_H
#define SUN_H
class Sun
{
    public:
        Sun(int inX,int inY);
        Sun();
        ~Sun();
         int Getx() { return x; }
        void Setx( int val) { x = val; }
         int Gety() { return y; }
        void Sety( int val) { y = val; }
         int GettimeLeft() { return timeLeft; }
        void SettimeLeft( int val) { timeLeft = val; }
         int GetsunValue() { return sunValue; }
        void SetsunValue( int val) { sunValue = val; }
         bool Getcollected() { return collected; }
        void Setcollected( bool val) { collected = val; }
        void init();
    protected:
    private:
         int x;
         int y;
         int timeLeft;
         int sunValue;
         bool collected;
};

#endif // SUN_H
