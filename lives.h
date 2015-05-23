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
	void onNotify();
    void render(QPainter &qpainter);
    void update();

private:
	int m_lives;
};

#endif // LIVES_H
