#ifndef OBSERVER
#define OBSERVER

class Observer
{
public:
    virtual ~Observer() {}
    virtual void onNotify() = 0;

};

#endif // OBSERVER

