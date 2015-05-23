#include "subject.h"
#include <iostream>
using namespace std;

void Subject::notify()
{
    for (Observer* i : m_observers)
    {
        if (i)
        {
            i->onNotify();
        }
    }
}

void Subject::addObserver(Observer *observer)
{
    m_observers.push_back(observer);
}

void Subject::removeObserver(Observer *observer)
{
    m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer));
}
