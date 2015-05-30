#ifndef OBSERVER
#define OBSERVER

#define COLLISION 0
#define POWERUP 1

class Observer
{
public:
    virtual ~Observer() {}
    virtual void onNotify(int change) = 0;

};

#endif // OBSERVER

