#ifndef CHARSTATS_H
#define CHARSTATS_H

#include <QPainter>
#include <QStaticText>
#include <sstream>
#include <string>

#include "stickman.h"
#include "stickmanadapter.h"
#include "observer.h"

class CharStats : public Observer
{
public:
    CharStats(Stickman *stickman, StickmanAdapter *stickmanAdapter);
    void render(QPainter &qpainter);
    void onNotify(int change);

private:
    Stickman *m_stickman;
    StickmanAdapter *m_stickmanAdapter;
    StickmanSize m_curSize;
    float m_curJumpForce;
};

#endif // CHARSTATS_H
