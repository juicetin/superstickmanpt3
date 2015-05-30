#ifndef SCORE_H
#define SCORE_H

#include <QPainter>
#include <QStaticText>
#include <sstream>
#include <string>

#include "observer.h"

class Score : public Observer
{
public:
    Score();
    void onNotify(int change);
    void render(QPainter &qpainter);
    void update();

private:
    int m_score;
};

#endif // SCORE_H
