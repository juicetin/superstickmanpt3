#ifndef SCORE_H
#define SCORE_H

#include <QPainter>
#include <QStaticText>
#include <sstream>
#include <string>

#include "observer.h"
#include "lives.h"

class Score : public Observer
{
public:
    Score(Lives *lives);
    void onNotify(int change);
    void render(QPainter &qpainter);
    void update(bool left, bool right);

    int getScore() const;

private:
    int m_score;
    Lives *m_lives;
};

#endif // SCORE_H
