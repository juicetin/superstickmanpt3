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
    void onNotify();
    void render(QPainter &qpainter);

private:
    int m_score;
};

#endif // SCORE_H