#ifndef LIVES_H
#define LIVES_H

#include <QPainter>
#include <QStaticText>
#include <sstream>
#include <string>
#include <cstdlib>

#include "observer.h"

class Lives : public Observer
{
public:
    Lives(int lives);
    void onNotify(int change);
    void render(QPainter &qpainter);
    bool update();

    int getLives() const;
    int getLivesLost() const;

private:
	int m_lives;
	int m_livesLost;
};

#endif // LIVES_H
