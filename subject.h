#ifndef SUBJECT
#define SUBJECT

#include <vector>
#include <algorithm>

#include "observer.h"

class Subject
{
public:
    void addObserver(Observer *observer);
    void removeObserver(Observer *observer);

protected:
    void notify(int change);

private:
//    Observer *m_observers[MAX_OBSERVERS];

    std::vector<Observer*> m_observers;
    int m_numObservers;
};

#endif // SUBJECT

